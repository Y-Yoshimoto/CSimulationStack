//
//  main.c
//  Heisenberg_MonteCarlo
//
//  Created by 吉本雄介 on 2015/08/12.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "SFMT.h"
#include "mpi.h"

#define PPI 2.0*M_PI //2π
#define THREADS 1

#define Size 120
#define SizeP Size+1
#define SizeM Size+4
double Numbers=Size*Size;

//モンテカルロパラメーター
#define Set_of_Bins     100 //瓶の数100
#define In_Bins         1000 //瓶内のデータ数10000

//モンテカルテ用
#define Initial_Relaxation 1e+5 //初期緩和1e+5
#define Data_Interval      10 //データ間隔10

//LLG用
#define tmax_Initial_Relaxation 1e+2 //初期緩和1e+3
#define tmax_Interval 100   //データ間隔1000

#define J  -1.0  //+強磁性体
//#define Dz 0.1 //+1軸異方性 -xy磁化容易面
double Hz=0.0,dHz;
double T=0.01,dT;
/*double Ja=0.0,Jb=0.0;
double Sa=1.0,Sb=1.0;
double Da=-0.1,Db=-0.1;*/
double Ja=0.0,Jb=0.0;
double Sa=1.0,Sb=1.0;
double Da=0.1,Db=0.1;
double ga=2.0,gb=2.0;

double beta;
double B[3]={0,0,0};

#define Hz_Partition 20 //オメガ分割数
//#define Hz_max 1.25
//#define Hz_min 1.20
#define Hz_max 10.1
#define Hz_min -0.2
#define Hz_Range Hz_max-Hz_min
#define T_Partition 20 //オメガ分割数
#define T_max 1.00
#define T_min 0.00
#define T_Range T_max-T_min


//MPI変数
int num_procs,myrank,name_len;
char processor_name[30];
int Start_Bin,End_Bin,Send_Bins;//瓶分割
int Right_Node,Left_Node;//レプリカ交換
int Send_Spins=Size*Size*3;//レプリカ交換
double R_beta,R_Hz,L_beta,L_Hz;
int Ex=0;//交換回数

//スピン配列とポインター配列
double Spin[Size][Size][3] = {0.0};
double *SP[SizeM][SizeM];
double S_zero[3]={0.0};
double Sab[SizeM][SizeM];
double Dab[SizeM][SizeM];
double Jab[SizeM][SizeM];
double MuGab[SizeM][SizeM];

#include "Ferri_Basic.h"
#include "Ferri_ReplicaExchange.h"
#include "Ferri_MonteCarlo.h"
#include "Ferri_LLG.h"
#include "Ferri_Sampling.h"

void One_T_Routine();
void T_Relaxation();
void MPI_Bin_Routine(FILE *);

//偶数個数

int main(int argc,char * argv[]) {
    //MPI設定
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Get_processor_name(processor_name, &name_len);

    //MPI瓶分割
    Send_Bins=Set_of_Bins/num_procs;    
    Start_Bin=Send_Bins*myrank;
    End_Bin=Send_Bins*(myrank+1);
    
    //MPIレプリカ交換
    Right_Node=myrank+1;
    Left_Node=myrank-1;
    if (myrank==0) Left_Node=num_procs-1;
    if (myrank==(num_procs-1)) Right_Node=0;
    //サンプリング関数内

    
    //温度(磁場),磁化,帯磁率,ビンダーパラメーター,エネルギー,比熱

    /*温度変化  
    T=(double)(myrank+1)/(double)num_procs*(T_max-T_min)+T_min;
    beta = 1.0/T;
    //Result[0]=T;
    R_beta=1.0/((double)(Right_Node+1)/(double)num_procs*(T_max-T_min)+T_min);
    L_beta=1.0/((double)(Left_Node+1)/(double)num_procs*(T_max-T_min)+T_min);
    R_Hz=Hz;
    L_Hz=Hz;*/

    //磁場変化
    Hz=(double)myrank/(double)num_procs*(Hz_max-Hz_min)+Hz_min;//磁場;
    dHz=((double)Hz_Range)/((double)Hz_Partition);
    beta = 1.0/T;
    R_Hz=(double)Right_Node/(double)num_procs*(Hz_max-Hz_min)+Hz_min;//磁場
    L_Hz=(double)Left_Node/(double)num_procs*(Hz_max-Hz_min)+Hz_min;//磁場
    R_beta=beta;
    L_beta=beta;

    Point_Set();
    Jab_Sab_Dab_set();
    RK4_KPoint_Set();

    //初期配置
    //Random_set();//ランダム配置
    //Ferro_set();//強磁性配置
    Z_Neel();
    
    One_T_Routine();

    
    MPI_Finalize();

    return 0;
}

void One_T_Routine()
{
    double Result[17]={0.0};
    double Gather_Result[num_procs][17];    
    beta = 1.0/T;
    Result[0]=Hz;
    
    Ex=0;
    
    //MonteCarlo_Routine(Result,myrank);
    //REx_MonteCarlo_Routine(Result,myrank);
    //LLG_MonteCarlo_Routine(Result,myrank);
    //MPI_MonteCarlo_Routine(Result,myrank);
    //MPI_MonteCarlo_Routine(Result,myrank);
    REx_MonteCarlo_LLG_Routine(Result,myrank);
    
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&Result[0],17,MPI_DOUBLE,&Gather_Result[myrank][0],17,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    
    int G_Ex[num_procs];
    MPI_Gather(&Ex,1,MPI_INT,&G_Ex[myrank],1,MPI_INT,0,MPI_COMM_WORLD);
    if (myrank==0)
    {
    char fname[64];
    //sprintf(fname,"result%.2lf.dat",T);
    sprintf(fname,"result.dat");
    FILE *FResult;
    int i;
    int A_Ex=0;
    FResult=fopen(fname,"w");
    fprintf(FResult,"#TorHz,M,Me,X,Xe,g,ge,E,Ee,C,Ce,sM,sMe,sX,sXe,sg,sge\n");
    for (i=0; i<num_procs; i++) {
            //printf("Rank=%d Ex=%d %d\n",i,G_Ex[i]);
            A_Ex=A_Ex+G_Ex[i];
            //fprintf(FResult,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",Gather_Result[i][0],Gather_Result[i][1],Gather_Result[i][2],Gather_Result[i][3],Gather_Result[i][4],Gather_Result[i][5],Gather_Result[i][6],Gather_Result[i][7],Gather_Result[i][8],Gather_Result[i][9],Gather_Result[i][10]);
            fprintf(FResult,"%lf ",Gather_Result[i][0]);//温度
            fprintf(FResult,"%lf %lf ",Gather_Result[i][1],Gather_Result[i][2]);//磁化,磁化誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][3],Gather_Result[i][4]);//帯磁率,帯磁率誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][5],Gather_Result[i][6]);//ビンダー,ビンダー誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][7],Gather_Result[i][8]);//エネルギー,エネルギー誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][9],Gather_Result[i][10]);//比熱,比熱誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][11],Gather_Result[i][12]);//スタッガード磁化,スタッガード磁化誤差
            fprintf(FResult,"%lf %lf ",Gather_Result[i][13],Gather_Result[i][14]);//スタッガード帯磁率,スタッガード帯磁率誤差
            fprintf(FResult,"%lf %lf\n",Gather_Result[i][15],Gather_Result[i][16]);//スタッガードビンダー,スタッガードビンダー誤差
    }
    fclose(FResult);
    printf("A_Ex=%d\n",A_Ex/num_procs);
    }
}
