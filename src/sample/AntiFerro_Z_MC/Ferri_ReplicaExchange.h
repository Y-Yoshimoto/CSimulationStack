//
//  Ferri_ReplicaExchange.h
//  Ferri_MonteCarlo
//
//  Created by 吉本雄介 on 2015/09/22.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#ifndef Ferri_MonteCarlo_Ferri_ReplicaExchange_h
#define Ferri_MonteCarlo_Ferri_ReplicaExchange_h

double Rspin[Size][Size][3] = {0.0};

void SpinMap_exchange(){
    int x,y;
    double Sx,Sy,Sz;
    for (x=0; x<Size; x++)
    {
        for (y=0; y<Size; y++)
        {
            Sx=Rspin[x][y][0];
            Sy=Rspin[x][y][1];
            Sz=Rspin[x][y][2];
            
            Rspin[x][y][0]=Spin[x][y][0];
            Rspin[x][y][1]=Spin[x][y][1];
            Rspin[x][y][2]=Spin[x][y][2];
            
            Spin[x][y][0]=Sx;
            Spin[x][y][1]=Sy;
            Spin[x][y][2]=Sz;
        }
    }
}

double S_Boltzmann_factor(double H_p,double beta_p)
{
    double Ene=0.0;
    int x,y;
    XYroopS
    double *c = SP[x][y];
    double *r = SP[x+1][y],*u = SP[x][y+1];
    double *nr = SP[x+2][y],*nu = SP[x][y+2];
    Ene+=-J*(c[0]*(r[0]+u[0]))-Jab[x][y]*(c[0]*(nr[0]+nu[0]))-B[0]*c[0];
    Ene+=-J*(c[1]*(r[1]+u[1]))-Jab[x][y]*(c[1]*(nr[1]+nu[1]))-B[1]*c[1];
    Ene+=-J*(c[2]*(r[2]+u[2]))-Jab[x][y]*(c[2]*(nr[2]+nu[2]))-B[2]*c[2]-H_p*c[2]-Dab[x][y]*c[2]*c[2];
    XYroopE
    Ene=Ene/Numbers;
    return exp(-beta_p*Ene);
}

void Replica_Exchange(int i,sfmt_t *sfmt){
    MPI_Status recv_status;
    MPI_Barrier(MPI_COMM_WORLD);
    int judge=0;
    //計算ノード
    if ((i+myrank)%2==0){//i_瓶番号
        double BF[2][2]={0.0};//ボルツマン因子_0OnMap,1Rigth_0分子1分母
        /*double E[2];
        E[0]=Energy();
        MPI_Recv(&E[1],1,MPI_DOUBLE,Right_Node,Right_Node,MPI_COMM_WORLD,&recv_status);
        double R=exp((E[0]-E[1])*(beta-R_beta));*/
        
        //エネルギー計算
        BF[0][0]=S_Boltzmann_factor(R_Hz,R_beta);//分子
        BF[0][1]=S_Boltzmann_factor(Hz,beta);//分母
        MPI_Recv(&BF[1][0],2,MPI_DOUBLE,Right_Node,Right_Node,MPI_COMM_WORLD,&recv_status);
        
        /*printf("Rank %d [0][0]%lf [1][0]%lf [0][1]%lf [1][1]%lf\n",myrank,BF[0][0],BF[1][0],BF[0][1],BF[1][1]);
        printf("Rank %d R_Hz=%lf R_beta=%lf\n",myrank,R_Hz,R_beta);
        printf("Rank %d Hz=%lf beta=%lf\n",myrank,Hz,beta);*/
        
        //確率計算
        double r=(BF[0][0]*BF[1][0])/(BF[0][1]*BF[1][1]);//交換する確率の計算
        /*
        if(myrank==3) {
        printf("Rank %d r=%lf dE=%lf\n",myrank,r,E[0]-E[1]);
        //printf("Rank %d E[0]=%lf E[1]=%lf\n",myrank,E[0],E[1]);
        //printf("[0][0]%lf [1][0]%lf [0][1]%lf [1][1]%lf\n",BF[0][0],BF[1][0],BF[0][1],BF[1][1]);
        }*/
        //メトロポリス
        if (r>=1.0) judge=1;
        else if (r>=sfmt_genrand_real3(sfmt)) judge=1;
        if (myrank==(num_procs-1)) judge=0; //端同士の交換を禁止
        //judge送信
        MPI_Send(&judge,1,MPI_INT,Right_Node,myrank,MPI_COMM_WORLD);
        
        if(judge==1){
            Ex++;
            //スピン受信
            MPI_Recv(&Rspin[0][0][0],Send_Spins,MPI_DOUBLE,Right_Node,Right_Node,MPI_COMM_WORLD,&recv_status);
            //スピンマップ入れ替え
            SpinMap_exchange();
            //スピン送信
            MPI_Send(&Rspin[0][0][0],Send_Spins,MPI_DOUBLE,Right_Node,myrank,MPI_COMM_WORLD);
        }
        //E[1]=Energy();
        //double P=exp((E[0]-E[1])*(beta-R_beta));
        //if(myrank==3) printf("SRSR %d E[0]=%lf E[1]=%lf\n",myrank,E[0],E[1]);
    }
    
    //待機ノード
    else{
        double BF_S[2]={0.0};//ボルツマン因子_Send_0分子1分母
        BF_S[0]=S_Boltzmann_factor(L_Hz,L_beta);//分子
        BF_S[1]=S_Boltzmann_factor(Hz,beta);//分母
        
        /*double Ene=Energy();
        MPI_Send(&Ene,1,MPI_DOUBLE,Left_Node,myrank,MPI_COMM_WORLD);*/

        
        /*printf("Rank %d S_[1][0]%lf S_[1][1]%lf\n",myrank,BF_S[0],BF_S[1]);
        printf("Rank %d L_Hz=%lf L_beta=%lf\n",myrank,L_Hz,L_beta);
        printf("Rank %d Hz=%lf beta=%lf\n",myrank,Hz,beta);*/

        MPI_Send(&BF_S[0],2,MPI_DOUBLE,Left_Node,myrank,MPI_COMM_WORLD);
        //judge受信
        MPI_Recv(&judge,1,MPI_INT,Left_Node,Left_Node,MPI_COMM_WORLD,&recv_status);
        
        if(judge==1){
            Ex++;
            //スピン送信
            MPI_Send(&Spin[0][0][0],Send_Spins,MPI_DOUBLE,Left_Node,myrank,MPI_COMM_WORLD);
            //printf("REx %d and %d\n",myrank,Left_Node);
            //スピン受信
            MPI_Recv(&Spin[0][0][0],Send_Spins,MPI_DOUBLE,Left_Node,Left_Node,MPI_COMM_WORLD,&recv_status);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

#endif
