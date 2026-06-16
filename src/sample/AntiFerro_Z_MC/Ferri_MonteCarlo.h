//
//  Heisenberg_MonteCarlo.h
//  Heisenberg_MonteCarlo
//
//  Created by 吉本雄介 on 2015/08/12.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#ifndef Ferri_MonteCarlo_Ferri_MonteCarlo_h
#define Ferri_MonteCarlo_Ferri_MonteCarlo_h

void MetloPolice(int x,int y,sfmt_t *sfmt)
{
    //最近接スピンの総和    //四方向のセッティング
    double CloseSpin[3]={0};
    double *l = SP[x-1][y],*r = SP[x+1][y],*d = SP[x][y-1],*u = SP[x][y+1];
    double N_CloseSpin[3]={0};
    double *nl = SP[x-2][y],*nr = SP[x+2][y],*nd = SP[x][y-2],*nu = SP[x][y+2];
    Sum_Close_Spins(CloseSpin,l,r,d,u);
    Sum_Close_Spins(N_CloseSpin,nl,nr,nd,nu);
    double Ssize=Sab[x][y];
    
    //中心スピンの設定
    double *CentralSpin=SP[x][y];
    //新スピンの設定
    double NewSpin[3]={0};
    {
        //printf("%d %lf\n",omp_get_thread_num(),sfmt_genrand_real2(sfmt));
        double z=sfmt_genrand_real1(sfmt)*2.0-1.0;
        //z=z/sqrt(z*z);//イジング化
        double R=sqrt(1.0-z*z);
        double phi=PPI*sfmt_genrand_real2(sfmt);
        NewSpin[0]=Ssize*R*cos(phi);
        NewSpin[1]=Ssize*R*sin(phi);
        NewSpin[2]=Ssize*z;
    }
    
    //エネルギー計算
    double Eold=Site_Energy(Jab[x][y],Dab[x][y],MuGab[x][y],CentralSpin,CloseSpin,N_CloseSpin);
    double Enew=Site_Energy(Jab[x][y],Dab[x][y],MuGab[x][y],NewSpin,CloseSpin,N_CloseSpin);
    double dE=Enew-Eold;
    
    //メトロポリス法
    if (dE<0) {
        CentralSpin[0]=NewSpin[0];
        CentralSpin[1]=NewSpin[1];
        CentralSpin[2]=NewSpin[2];
    }
    else {
        if (exp(-beta*dE)>=sfmt_genrand_real3(sfmt)) {
            CentralSpin[0]=NewSpin[0];
            CentralSpin[1]=NewSpin[1];
            CentralSpin[2]=NewSpin[2];
        }
    }      
    //#pragma omp barrier  
}
//指定回数シングルフリップMCステップ
void Repetitive_MC_Step(int ms_Step,sfmt_t *sfmt){
    int i,x,y;
    for (i = 0; i < ms_Step; i++) {
        //1モンテカルロステップ
        #pragma omp for private(y) collapse(2)
        XYroopS
            MetloPolice(x, y,sfmt);
        XYroopE
    }
    #pragma omp barrier
}
//平均値と分散,標準誤
void Average_and_Variance(double *Data,double *Retarn){
    double Average=0.0,Square=0.0;
    double RSBin=1.0/((double)Set_of_Bins);
    int i;
    for (i=0; i<Set_of_Bins; i++) {
        Average+=Data[i];
        Square+=(Data[i]*Data[i]);
    }
    Average=Average*RSBin;
    Square=Square*RSBin;
    double Variance=Square-Average*Average;
    *Retarn=Average;
    //*(Retarn+1)=sqrt(Variance);//標準偏差
    //*(Retarn+1)=sqrt(Variance*RSBin);//標準誤差_67%信頼区間
    *(Retarn+1)=2.0*sqrt(Variance*RSBin);//標準誤差_95%信頼区間
}
//瓶セットを埋める
void Bottling_a_Bin(double *M,double *X,double *g,double *E,double *C,double *sM,double *sX,double *sg,sfmt_t *sfmt){
    double RIBin=1.0/((double)In_Bins);//瓶内のデータ数の逆数
    int i;
    double Mag[3]={0.0};
    double sMag[3]={0.0};
    double Ene[2]={0.0};
    for (i=0; i<In_Bins;i++){
        Repetitive_MC_Step(Data_Interval,sfmt);//データ間隔
        //物理量の測定
        #pragma omp master
        {
            double pM=Magnetization();
            double pE=Energy();
            double psM=Staggered_Magnetization();
            Mag[0]+=pM;
            Mag[1]+=(pM*pM);
            Mag[2]+=(pM*pM*pM*pM);
            Ene[0]+=pE;
            Ene[1]+=(pE*pE);
            psM=sqrt(psM*psM);  //Zスタッガードの絶対値
            sMag[0]+=psM;
            sMag[1]+=(psM*psM);
            sMag[2]+=(psM*psM*psM*psM);
        }
    }
    #pragma omp barrier
    #pragma omp master
    {
        *M=Mag[0]*RIBin;
        *X=(Mag[1]*RIBin-*M**M)*beta*(double)Numbers;
        *g=0.5*(3.0-(Mag[2]*RIBin)/(Mag[1]*RIBin*Mag[1]*RIBin));
        *E=Ene[0]*RIBin;
        *C=(Ene[1]*RIBin-*E**E)*beta*beta*(double)Numbers;
        *sM=sMag[0]*RIBin;
        *sX=(sMag[1]*RIBin-*sM**sM)*beta*(double)Numbers;
        *sg=0.5*(3.0-(sMag[2]*RIBin)/(sMag[1]*RIBin*sMag[1]*RIBin));
    }
}
//モンテカルロルーチンの開始
void MonteCarlo_Routine(double *Result,int myrank){
    //物理量用の瓶の設定
    double M[Set_of_Bins],X[Set_of_Bins],g[Set_of_Bins],E[Set_of_Bins],C[Set_of_Bins],sM[Set_of_Bins],sX[Set_of_Bins],sg[Set_of_Bins];

    #pragma omp parallel num_threads(THREADS)
    {
        sfmt_t sfmt;
        sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num()+myrank*100);
        //printf("%d %lf\n",omp_get_thread_num(),sfmt_genrand_real2(&sfmt));
        //初期緩和
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);
        int j;
        for (j=0; j<10; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        #pragma omp master
        {
                //Replica_Exchange(j,&sfmt);
        }
        }
        
        //物理量の測定
        int i;
        for (i=0; i<Set_of_Bins; i++) {
            Repetitive_MC_Step(tmax_Interval,&sfmt);
            Bottling_a_Bin(&M[i],&X[i],&g[i],&E[i],&C[i],&sM[i],&sX[i],&sg[i],&sfmt);
        #pragma omp barrier 
        #pragma omp master
        {
                //Replica_Exchange(i,&sfmt);
                if (myrank==0){
                printf("%d/%d\n",i,Set_of_Bins);
                 }
        }
        #pragma omp barrier 
        }
    }
    //Retarn
    Average_and_Variance(M,&Result[1]);//磁化
    Average_and_Variance(X,&Result[3]);//帯磁率
    Average_and_Variance(g,&Result[5]);//ビンダーパラメーター
    Average_and_Variance(E,&Result[7]);//エネルギー
    Average_and_Variance(C,&Result[9]);//比熱
    Average_and_Variance(sM,&Result[11]);//スタッガード磁化
    Average_and_Variance(sX,&Result[13]);//スタッガード帯磁率
    Average_and_Variance(sg,&Result[15]);//スタッガードビンダーパラメーター
}
/*
void REx_MonteCarlo_Routine(double *Result,int myrank){
    //物理量用の瓶の設定
    double M[Set_of_Bins],X[Set_of_Bins],g[Set_of_Bins],E[Set_of_Bins],C[Set_of_Bins],sM[Set_of_Bins],sX[Set_of_Bins],sg[Set_of_Bins];

    #pragma omp parallel num_threads(THREADS)
    {
        sfmt_t sfmt;
        sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num()+myrank*100);
        //printf("%d %lf\n",omp_get_thread_num(),sfmt_genrand_real2(&sfmt));
        //初期緩和
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);
        int j;
        for (j=0; j<10; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        #pragma omp master
        {
                Replica_Exchange(j,&sfmt);
        }
        }
        
        //物理量の測定
        int i;
        for (i=0; i<Set_of_Bins; i++) {
            Repetitive_MC_Step(tmax_Interval,&sfmt);
            Bottling_a_Bin(&M[i],&X[i],&g[i],&E[i],&C[i],&sM[i],&sX[i],&sg[i],&sfmt);
        #pragma omp barrier 
        #pragma omp master
        {
                Replica_Exchange(i,&sfmt);
                if (myrank==0){
                printf("%d/%d\n",i,Set_of_Bins);
                 }
        }
        #pragma omp barrier 
        }
    }
    //Retarn
    Average_and_Variance(M,&Result[1]);//磁化
    Average_and_Variance(X,&Result[3]);//帯磁率
    Average_and_Variance(g,&Result[5]);//ビンダーパラメーター
    Average_and_Variance(E,&Result[7]);//エネルギー
    Average_and_Variance(C,&Result[9]);//比熱
    Average_and_Variance(sM,&Result[11]);//スタッガード磁化
    Average_and_Variance(sX,&Result[13]);//スタッガード帯磁率
    Average_and_Variance(sg,&Result[15]);//スタッガードビンダーパラメーター
}
*/
#endif
