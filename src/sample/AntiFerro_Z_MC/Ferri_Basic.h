//
//  Heisenberg_Basic.h
//  Heisenberg_MonteCarlo
//
//  Created by 吉本雄介 on 2015/08/19.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#ifndef Ferri_MonteCarlo_Ferri_Basic_h
#define Ferri_MonteCarlo_Ferri_Basic_h

#define XYroopS     for (x=2 ; x<=SizeP ; x++){for (y=2; y<=SizeP; y++){
#define XYroopE     }}

void Laser(double t);

//ワンサイトのエネルギー
double Site_Energy(double J_n,double D,double mug,double *c,double *s,double *n){
    double Ene=0.0;
    Ene=-J*(c[0]*s[0])-J_n*(c[0]*n[0])-mug*B[0]*c[0];
    Ene+=-J*(c[1]*s[1])-J_n*(c[1]*n[1])-mug*B[1]*c[1];
    Ene+=-J*(c[2]*s[2])-J_n*(c[2]*n[2])-mug*Hz*c[2]-mug*B[2]*c[2]-D*c[2]*c[2];
    return Ene;
}
//近接スピンの合計
void Sum_Close_Spins(double *CloseSpin,double *l,double *r,double *d,double *u){
    //総和の計算
    *CloseSpin=(l[0]+r[0]+d[0]+u[0]);
    *(CloseSpin+1)=(l[1]+r[1]+d[1]+u[1]);
    *(CloseSpin+2)=(l[2]+r[2]+d[2]+u[2]);
}

//ポインターマップのセット
void Point_Set(){
    int x,y;
    //初期化
    for (x=0; x<SizeM; x++)
    {
        for (y=0; y<SizeM; y++)
        {
        SP[x][y] = S_zero;
        }
    }
    
    for (x=0; x<Size; x++)
    {
        for (y=0; y<Size; y++)
        {
            SP[x+2][y+2] = &Spin[x][y][0];
            /*境界部分の配置
            if(x == 0) SP[Size+1][y+1] = &Spin[0][y][0];
            if(y == 0) SP[x+1][Size+1] = &Spin[x][0][0];
            if(x == (Size-1)) SP[0][y+1] = &Spin[Size-1][y][0];
            if(y == (Size-1)) SP[x+1][0] = &Spin[x][Size-1][0];
            */
        }
    }
    /*四隅の設定
    SP[Size+1][Size+1] = &Spin[0][0][0];
    SP[0][Size+1] = &Spin[Size-1][0][0];
    SP[Size+1][0] = &Spin[0][Size-1][0];
    SP[0][0] = &Spin[Size-1][Size-1][0];
    */
}
/**********初期配置**********/
//ランダム配置
void Random_set(){
    sfmt_t sfmt;
    sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+myrank);
    int x,y;
    XYroopS{
        double z=sfmt_genrand_real1(&sfmt)*2.0-1.0;
        //z=z/sqrt(z*z);//イジング化
        double R=sqrt(1-z*z);
        double phi=PPI*sfmt_genrand_real2(&sfmt);
        *SP[x][y]=R*cos(phi);
        *(SP[x][y]+1)=R*sin(phi);
        *(SP[x][y]+2)=z;
    }XYroopE
}
//+Z強磁性配置
void Ferro_set(){
    int x,y;
    XYroopS
        *SP[x][y]=0.0;
        *(SP[x][y]+1)=0.0;
        *(SP[x][y]+2)=1.0*Sab[x][y];
    XYroopE
}
//Z反強磁性配置
void Z_Neel(){
    double f=1.0;//フリップ変数
    int x,y;
    XYroopS
        *SP[x][y]=0.0;
        *(SP[x][y]+1)=0.0;
        *(SP[x][y]+2)=1.0*f*Sab[x][y];
        //printf("%d %d %lf\n",x,y,f);
        f=(-f);
    }f=(-f);}
}
//X反強磁性配置
void X_Neel(){
    double f=1.0;//フリップ変数
    int x,y;
    XYroopS
        *SP[x][y]=1.0*f*Sab[x][y];
        *(SP[x][y]+1)=0.0;
        *(SP[x][y]+2)=0.0;
        //printf("%d %d %lf\n",x,y,f);
        f=(-f);
    }f=(-f);}
}

//SF反強磁性配置
void SF_Antiferromagnetic(){
    double f=1.0;//フリップ変数
    double theta =0.0;
    //if (z >=1.0) z=1.0;
    //if (z <=-1.0) z=-1.0;
    int x,y;
    XYroopS
        double z=Hz/(2.0*(4.0-Dab[x][y]));
        double R=sqrt(1-z*z);
        *SP[x][y]=Sab[x][y]*R*f*cos(theta);
        *(SP[x][y]+1)=Sab[x][y]*R*f*sin(theta);
        *(SP[x][y]+2)=Sab[x][y]*z;
        f=(-f);
    }f=(-f);}
}
/**************************/

void Jab_Sab_Dab_set(){
    int x,y;
    double f=1.0;//フリップ変数
    XYroopS
        if (f>0) {
            Dab[x][y]=Da;
            Sab[x][y]=Sa;
            Jab[x][y]=Ja;
            MuGab[x][y]=ga/2.0;
            }
        else{
        Dab[x][y]=Db;
        Sab[x][y]=Sb;
        Jab[x][y]=Jb;
        MuGab[x][y]=gb/2.0;
        }
        f=(-f);
    }f=(-f);}
}

/**********物理量測定**********/
 //系全体のエネルギー
double Energy()
{
    double Ene=0.0;
    int x,y;
    XYroopS
    double *c = SP[x][y];
    double *r = SP[x+1][y],*u = SP[x][y+1];
    double *nr = SP[x+2][y],*nu = SP[x][y+2];
    Ene+=-J*(c[0]*(r[0]+u[0]))-Jab[x][y]*(c[0]*(nr[0]+nu[0]))-MuGab[x][y]*B[0]*c[0];
    Ene+=-J*(c[1]*(r[1]+u[1]))-Jab[x][y]*(c[1]*(nr[1]+nu[1]))-MuGab[x][y]*B[1]*c[1];
    Ene+=-J*(c[2]*(r[2]+u[2]))-Jab[x][y]*(c[2]*(nr[2]+nu[2]))-MuGab[x][y]*B[2]*c[2]-MuGab[x][y]*Hz*c[2]-Dab[x][y]*c[2]*c[2];
    XYroopE
    return Ene/Numbers;
}
//系全体のZ方向の磁化
double Magnetization()
{
    double Mag=0.0;
    int x,y;
    XYroopS
    Mag+=*(SP[x][y]+2);
    XYroopE
    return Mag/Numbers;
}

//系全体のスタッカード磁化
double Staggered_Magnetization()
{
    double f=1.0;//フリップ変数
    double Mag=0.0;
    int x,y;for (x=1 ; x<=Size ; x++){for (y=1; y<=Size; y++){
        Mag+=(*(SP[x][y]+2)*f);
        //printf("%d %d   %lf\n",x,y,*(SP[x][y]+2)*f);
        f=(-f);
    }f=(-f);}
    return Mag/Numbers;
}
/***************************/

void Spin_map(int i)
{
    char fname[32];
    FILE *Map;
    sprintf(fname,"./Map/Spin_map%02d.dat",i);
    Map=fopen(fname,"w");
    //fprintf(Map,"#Hx=%0.2lf Hy=%0.2lf Hz=%0.2lf\n",B[0],B[1],B[2]);
    int x,y;
    for (x=1 ; x<SizeM ; x++)
    {
        for (y=1 ; y<SizeM ; y++)
        {
            double *p=SP[x][y];
            fprintf(Map,"%d %d %d %lf %lf %lf\n",x,y,0,*p,*(p+1),*(p+2));
        }
        fprintf(Map,"\n");
    }
    printf("%d\n",i);
    fclose(Map);
}

//周期部分も含めたスピンマップの出力
void Spinmap_Print(){
    int x,y;
    for (x=0; x<SizeM; x++)
    {
        for (y=0; y<SizeM; y++)
        {
            double *p=SP[x][y];
            printf("%.2lf ",sqrt(p[0]*p[0]+p[1]*p[1]+p[2]*p[2]));
        }
        printf("\n");
    }
}

void AB_Print(){
    int x,y;
    for (x=0; x<SizeM; x++)
    {
        for (y=0; y<SizeM; y++)
        {
            //printf("%.2lf ",Dab[x][y]);
            //printf("%.2lf ",Sab[x][y]);
            printf("%.2lf ",Jab[x][y]);
        }
        printf("\n");
    }
}
/*
void Mvector(FILE *Mresult,int Splot,int Eplot,int N,double t)
{
    int x,y,Nh=(Splot+Eplot)/2;
    double M[3]={0};
    //Laser(t);
    double BAmplitude=sqrt(B[0]*B[0]+B[1]*B[1]+B[2]*B[2]);
    for (x= Splot; x<Eplot ; x++)
    {
        for (y=Splot ; y<Eplot ; y++)
        {
            M[0]+=Spin[x][y][0];
            M[1]+=Spin[x][y][1];
            M[2]+=Spin[x][y][2];
        }
    }
    //全体
    M[0]=M[0]/(double)N;
    M[1]=M[1]/(double)N;
    M[2]=M[2]/(double)N;

    //ユニタリー変換回転座標系
    //double xr=M[0]*cos(Omega*t)+M[1]*sin(Omega*t);
    //double yr=-M[0]*sin(Omega*t)+M[1]*cos(Omega*t);
    //double xr=M[0]*cos(HZ*t)+M[1]*sin(HZ*t);
    //double yr=-M[0]*sin(HZ*t)+M[1]*cos(HZ*t);
    //fprintf(Mresult,"%lf %lf %lf %lf %lf %lf %lf %lf %5e ",t,xr,yr,M[2],BAmplitude,B[0],B[1],B[2],Asum);
    
    fprintf(Mresult,"%lf %lf %lf %lf %lf %lf %lf %lf %lf ",t,M[0],M[1],M[2],BAmplitude,B[0],B[1],B[2],Asum);
    //1スピン
    M[0]=Spin[Nh][Nh][0];
    M[1]=Spin[Nh][Nh][1];
    M[2]=Spin[Nh][Nh][2];
    fprintf(Mresult,"%lf %lf %lf ",M[0],M[1],M[2]);
    //1スピン
    M[0]=Spin[Nh][Nh+1][0];
    M[1]=Spin[Nh][Nh+1][1];
    M[2]=Spin[Nh][Nh+1][2];
    fprintf(Mresult,"%lf %lf %lf\n",M[0],M[1],M[2]); 
}*/
#endif
