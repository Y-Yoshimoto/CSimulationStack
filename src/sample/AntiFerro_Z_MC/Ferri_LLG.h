//
//  Heisenberg_LLG.h
//  Heisenberg_MonteCarlo
//
//  Created by 吉本雄介 on 2015/08/19.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#ifndef Ferri_MonteCarlo_Ferri_LLG_h
#define Ferri_MonteCarlo_Ferri_LLG_h

#define a 2.0e-2
double A=1.0/(1.0+a*a);//緩和定数の変更
#define Delta_t 0.02
double dt=Delta_t;
double hdt=Delta_t/2.0;
double dSixt=Delta_t/6.0;

void RK4_KPoint_Set();
double K[3][Size][Size][3]={0};
double *KP0[SizeM][SizeM];
double *KP13[SizeM][SizeM];
double *KP24[SizeM][SizeM];

double Nimage=100;

#define Array_size Size*Size*3
//uint64_t array[Array_size];
double Force[SizeM][SizeM][3]={0};
double RF_sigma;
void Force_set(sfmt_t *sfmt)
{
    int x,y;
    double Z1,Z2;
    double RF_sigma=sqrt(2.0*a/(dt*beta));
    #pragma omp for private(y,Z1,Z2)
    XYroopS
    Z1=sqrt(-2.0*log(sfmt_genrand_real3(sfmt)))*RF_sigma;
    Z2=PPI*sfmt_genrand_real3(sfmt);
    Force[x][y][0]=Z1*cos(Z2);
    Force[x][y][1]=Z1*sin(Z2);
    
    Z1=sqrt(-2.0*log(sfmt_genrand_real3(sfmt)))*RF_sigma;
    Z2=PPI*sfmt_genrand_real3(sfmt);
    Force[x][y][2]=Z1*cos(Z2);
    y++;
    Force[x][y][0]=Z1*sin(Z2);
    
    Z1=sqrt(-2.0*log(sfmt_genrand_real3(sfmt)))*RF_sigma;
    Z2=PPI*sfmt_genrand_real3(sfmt);
    Force[x][y][1]=Z1*cos(Z2);
    Force[x][y][2]=Z1*sin(Z2);
    XYroopE
}
//ハミルトニアンx,y,zの微分
void dHxyz(double J_n,double D,double mug,double *c,double *s,double *n,double* dH)//dH/dmx
{
    dH[0]=(-J*s[0]-J_n*n[0]-mug*B[0]);
    dH[1]=(-J*s[1]-J_n*n[1]-mug*B[1]);
    dH[2]=(-J*s[2]-J_n*n[2]-mug*B[2]-mug*Hz-2.0*D*c[2]);
}
void dsdH(int x,int y,double *c,double *s,double *n,double *dk,double *F)
{
    double dH[3],mdH[3];//計算用dH
    dHxyz(Jab[x][y],Dab[x][y],MuGab[x][y],c,s,n,dH);
    
    dH[0]+=F[0];
    dH[1]+=F[1];
    dH[2]+=F[2];
    
    mdH[0]=c[2]*dH[1]-c[1]*dH[2];
    mdH[1]=c[0]*dH[2]-c[2]*dH[0];
    mdH[2]=c[1]*dH[0]-c[0]*dH[1];
    
    dk[0]=A*(a*(c[2]*mdH[1]-c[1]*mdH[2])-mdH[0]);
    dk[1]=A*(a*(c[0]*mdH[2]-c[2]*mdH[0])-mdH[1]);
    dk[2]=A*(a*(c[1]*mdH[0]-c[0]*mdH[1])-mdH[2]);
}

void K1(int x,int y)
{
    double dk[3];//計算用スピン配列
    double *CS=SP[x][y];
    
    double Side[3]={0};
    double *l=SP[x-1][y],*r=SP[x+1][y],*d=SP[x][y-1],*u=SP[x][y+1];
    
    double N_Side[3]={0};
    double *nl=SP[x-2][y],*nr=SP[x+2][y],*nd=SP[x][y-2],*nu=SP[x][y+2];
    
    Sum_Close_Spins(Side,l,r,d,u);
    Sum_Close_Spins(N_Side,nl,nr,nd,nu);
    
    double *F=&Force[x][y][0];
    dsdH(x,y,CS,Side,N_Side,dk,F);
    
    //最終的なKの足し算
    *(KP0[x][y]+0)=dk[0];
    *(KP0[x][y]+1)=dk[1];
    *(KP0[x][y]+2)=dk[2];
    
    //次で使うK
    *(KP13[x][y]+0)=CS[0]+hdt*dk[0];
    *(KP13[x][y]+1)=CS[1]+hdt*dk[1];
    *(KP13[x][y]+2)=CS[2]+hdt*dk[2];
}
void K2(int x,int y)
{
    double dk[3];//計算用スピン配列
    double *CS=KP13[x][y];
    
    double Side[3]={0};
    double *l=KP13[x-1][y],*r=KP13[x+1][y],*d=KP13[x][y-1],*u=KP13[x][y+1];
    double N_Side[3]={0};
    double *nl=KP13[x-2][y],*nr=KP13[x+2][y],*nd=KP13[x][y-2],*nu=KP13[x][y+2];
    Sum_Close_Spins(Side,l,r,d,u);
    Sum_Close_Spins(N_Side,nl,nr,nd,nu);
    
    double *F=&Force[x][y][0];
    dsdH(x,y,CS,Side,N_Side,dk,F);
    //最終的なKの足し算
    
    *(KP0[x][y]+0)+=(2.0*dk[0]);
    *(KP0[x][y]+1)+=(2.0*dk[1]);
    *(KP0[x][y]+2)+=(2.0*dk[2]);
    
    //次で使うK
    CS=SP[x][y];//元々スピンマップ
    *(KP24[x][y]+0)=CS[0]+hdt*dk[0];
    *(KP24[x][y]+1)=CS[1]+hdt*dk[1];
    *(KP24[x][y]+2)=CS[2]+hdt*dk[2];
}
void K3(int x,int y)
{
    double dk[3];//計算用スピン配列
    double *CS=KP24[x][y];
    double Side[3]={0};
    double *l=KP24[x-1][y],*r=KP24[x+1][y],*d=KP24[x][y-1],*u=KP24[x][y+1];
    double N_Side[3]={0};
    double *nl=KP24[x-2][y],*nr=KP24[x+2][y],*nd=KP24[x][y-2],*nu=KP24[x][y+2];
    Sum_Close_Spins(Side,l,r,d,u);
    Sum_Close_Spins(N_Side,nl,nr,nd,nu);
    
    double *F=&Force[x][y][0];
    dsdH(x,y,CS,Side,N_Side,dk,F);
    //最終的なKの足し算
    *(KP0[x][y]+0)+=(2.0*dk[0]);
    *(KP0[x][y]+1)+=(2.0*dk[1]);
    *(KP0[x][y]+2)+=(2.0*dk[2]);
    
    //次で使うK
    CS=SP[x][y];//元々スピンマップ
    *(KP13[x][y]+0)=CS[0]+dt*dk[0];
    *(KP13[x][y]+1)=CS[1]+dt*dk[1];
    *(KP13[x][y]+2)=CS[2]+dt*dk[2];
}
void K4(int x,int y)
{
    double dk[3];//計算用スピン配列
    double *CS=KP13[x][y];
    
    double Side[3]={0};
    double *l=KP13[x-1][y],*r=KP13[x+1][y],*d=KP13[x][y-1],*u=KP13[x][y+1];
    double N_Side[3]={0};
    double *nl=KP13[x-2][y],*nr=KP13[x+2][y],*nd=KP13[x][y-2],*nu=KP13[x][y+2];
    Sum_Close_Spins(Side,l,r,d,u);
    Sum_Close_Spins(N_Side,nl,nr,nd,nu);

    
    double *F=&Force[x][y][0];
    dsdH(x,y,CS,Side,N_Side,dk,F);
    //最終的なKの足し算
    *(KP0[x][y]+0)+=dk[0];
    *(KP0[x][y]+1)+=dk[1];
    *(KP0[x][y]+2)+=dk[2];
}
void Normalization(int x,int y)
{
    double *CS=SP[x][y];
    double *dk=KP0[x][y];
    double NS[3]={0.0};
    NS[0]=CS[0]+dSixt*dk[0];
    NS[1]=CS[1]+dSixt*dk[1];
    NS[2]=CS[2]+dSixt*dk[2];
    
    double nc=Sab[x][y]/sqrt(NS[0]*NS[0]+NS[1]*NS[1]+NS[2]*NS[2]);
    
    CS[0]=nc*NS[0];
    CS[1]=nc*NS[1];
    CS[2]=nc*NS[2];
}
void LLG_RK4_Step(double t,sfmt_t *sfmt)
{
    int x,y;
    Force_set(sfmt);
    
    //K1
    #pragma omp for private(y) collapse(2)
    XYroopS
    K1(x,y);
    XYroopE
    
    t+=hdt;
        
    //K2
    #pragma omp for private(y) collapse(2)
    XYroopS
    K2(x,y);
    XYroopE
    
    //K3
    #pragma omp for private(y) collapse(2)
    XYroopS
    K3(x,y);
    XYroopE
    
    t+=hdt;
    
    //K4
    #pragma omp for private(y) collapse(2)
    XYroopS
    K4(x,y);
    XYroopE
    
    //SUM
    #pragma omp for private(y) collapse(2)
    XYroopS
    Normalization(x,y);
    XYroopE
}
/*
void LLG_Routine(double tmax)
{
    int i=0,j=0;
    int imax=(tmax/dt);
    int igun=imax/Nimage;//ループ回数,描画間隔
    FILE *GnuS;
    GnuS=fopen("./Spingif.plt","w");
    //printf("igun=%d\n",igun);
    gnu_Spin_gif(GnuS,0,SizeM);
    Spin_map(i);
    #pragma omp parallel num_threads(THREADS)
    {
    double t=0.0;
    sfmt_t sfmt;
    sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num());
    while (t < tmax) {
        LLG_RK4_Step(t,&sfmt);
        t+=dt;
        #pragma omp master
        {
        i++;
        if (i%igun==0){
            j++;
            //printf("i=%d / %d\n",i,imax);
            Spin_map(j);
            //printf("E=%lf M=%lf sM=%lf\n",Energy(),Magnetization(),Staggered_Magnetization());
            
        }
        }
    }
    }
    j++;
    Spin_map(GnuS,j);
    fprintf(GnuS, "set output");
    fclose(GnuS);
}
void MC_Routine(int imax)
{
    int igun=imax/Nimage;//ループ回数,描画間隔
    FILE *GnuS;
    GnuS=fopen("./Spingif.plt","w");
    printf("igun=%d %d \n",igun,imax);
    gnu_Spin_gif(GnuS,0,SizeM);
    //Spin_map(i);
    #pragma omp parallel num_threads(THREADS)
    {
    int i=0,j=0;
    sfmt_t sfmt;
    sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num());
    for (i=0; i<imax; i++) {
        Repetitive_MC_Step(1,&sfmt);
        #pragma omp master
        {
        if (i%igun==0){
            j++;
            //printf("i=%d / %d\n",i,imax);
            Spin_map(j);
        }
        }
    }
    }
    //j++;
    //Spin_map(GnuS,j);
    fprintf(GnuS, "set output");
    fclose(GnuS);
}*/


void LLG_Relaxation(double tmax,sfmt_t *sfmt)
{
        double t=0.0;
        while (t < tmax) {
            LLG_RK4_Step(t,sfmt);
            t+=dt;
        }
}

void LLG_Bottling_a_Bin(double *M,double *X,double *g,double *E,double *C,double *sM,double *sX,double *sg,sfmt_t *sfmt){
    double RIBin=1.0/((double)In_Bins);//瓶内のデータ数の逆数
    int i;
    double Mag[3]={0.0};
    double sMag[3]={0.0};
    double Ene[2]={0.0};
    for (i=0; i<In_Bins; i++){

        LLG_Relaxation(tmax_Interval,sfmt);

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
void LLG_MonteCarlo_Routine(double *Result,int myrank){
    //物理量用の瓶の設定
    double M[Set_of_Bins],X[Set_of_Bins],g[Set_of_Bins],E[Set_of_Bins],C[Set_of_Bins],sM[Set_of_Bins],sX[Set_of_Bins],sg[Set_of_Bins];
    RK4_KPoint_Set();
        
    #pragma omp parallel num_threads(THREADS)
    {
        sfmt_t sfmt;
        sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num()+myrank*100);
    
    //初期緩和
    LLG_Relaxation(tmax_Initial_Relaxation,&sfmt);
    
    //物理量の測定
    int i;
    for (i=0; i<Set_of_Bins; i++) {
        LLG_Bottling_a_Bin(&M[i],&X[i],&g[i],&E[i],&C[i],&sM[i],&sX[i],&sg[i],&sfmt);
        #pragma omp master
        {
                if (myrank==0){printf("%d/%d\n",i,Set_of_Bins);}
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
void RK4_KPoint_Set(){
    int x,y;
    
        //初期化
    for (x=0; x<SizeM; x++)
    {
        for (y=0; y<SizeM; y++)
        {
        KP0[x][y] = S_zero;
        KP13[x][y] = S_zero;
        KP24[x][y] = S_zero;
        }
    }
    
    for (x=0; x<Size; x++)
    {
        
        for (y=0; y<Size; y++)
        {
            KP0[x+2][y+2] = &K[0][x][y][0];
            KP13[x+2][y+2] = &K[1][x][y][0];
            KP24[x+2][y+2] = &K[2][x][y][0];
            /*境界部分の配置
            if(x == 0) {
                KP0[Size+1][y+1] = &K[0][0][y][0];
                KP13[Size+1][y+1] = &K[1][0][y][0];
                KP24[Size+1][y+1] = &K[2][0][y][0];
            }
            if(y == 0) {
                KP0[x+1][Size+1] = &K[0][x][0][0];
                KP13[x+1][Size+1] = &K[1][x][0][0];
                KP24[x+1][Size+1] = &K[2][x][0][0];
            }
            if(x == (Size-1)) {
                KP0[0][y+1] = &K[0][Size-1][y][0];
                KP13[0][y+1] = &K[1][Size-1][y][0];
                KP24[0][y+1] = &K[2][Size-1][y][0];
            }
            if(y == (Size-1)) {
                KP0[x+1][0] = &K[0][x][Size-1][0];
                KP13[x+1][0] = &K[1][x][Size-1][0];
                KP24[x+1][0] = &K[2][x][Size-1][0];
            }*/
        }
    }
    /*
    KP0[Size+1][Size+1] = &K[0][0][0][0];
    KP0[0][Size+1] = &K[0][Size-1][0][0];
    KP0[Size+1][0] = &K[0][0][Size-1][0];
    KP0[0][0] = &K[0][Size-1][Size-1][0];
    
    KP13[Size+1][Size+1] = &K[1][0][0][0];
    KP13[0][Size+1] = &K[1][Size-1][0][0];
    KP13[Size+1][0] = &K[1][0][Size-1][0];
    KP13[0][0] = &K[1][Size-1][Size-1][0];
    
    KP24[Size+1][Size+1] = &K[2][0][0][0];
    KP24[0][Size+1] = &K[2][Size-1][0][0];
    KP24[Size+1][0] = &K[2][0][Size-1][0];
    KP24[0][0] = &K[2][Size-1][Size-1][0];*/
}

#endif
