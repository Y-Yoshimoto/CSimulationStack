//
//  Heisenberg_Sampling.h
//  Heisenberg_MonteCarlo
//
//  Created by 吉本雄介 on 2015/09/10.
//  Copyright (c) 2015年 吉本雄介. All rights reserved.
//

#ifndef Ferri_MonteCarlo_Ferri_Sampling_h
#define Ferri_MonteCarlo_Ferri_Sampling_h

void MPI_MonteCarlo_Routine(double *Result,int myrank){
    //物理量用の瓶の設定
    double M[Set_of_Bins],X[Set_of_Bins],g[Set_of_Bins],E[Set_of_Bins],C[Set_of_Bins],sM[Set_of_Bins],sX[Set_of_Bins],sg[Set_of_Bins];
    RK4_KPoint_Set();
    #pragma omp parallel num_threads(THREADS)
    {
        sfmt_t sfmt;
        sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num()+myrank*100);
        //printf("%d %lf\n",omp_get_thread_num(),sfmt_genrand_real2(&sfmt));
        
        /*初期緩和
        int j;
        for (j=0; j<100; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        LLG_Relaxation(Data_Interval,&sfmt);
        }
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);

        for (j=0; j<100; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        LLG_Relaxation(Data_Interval,&sfmt);
        }
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);
        */
         #pragma omp master
        {printf("Start%d\n",myrank);}
        
        //物理量の測定
        int i;
        for (i=0; i<Set_of_Bins; i++) {
            Repetitive_MC_Step(tmax_Interval,&sfmt);
            LLG_Relaxation(Data_Interval,&sfmt);
            Bottling_a_Bin(&M[i],&X[i],&g[i],&E[i],&C[i],&sM[i],&sX[i],&sg[i],&sfmt);
        #pragma omp barrier 
        #pragma omp master
        {
                if (myrank==0){
                printf("%d/%d\n",i,Set_of_Bins);
                 }
        }
        #pragma omp barrier 
        }
    }
    
            printf("END %d\n",myrank);
    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank==0){
                printf("Gather\n");
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

void REx_MonteCarlo_LLG_Routine(double *Result,int myrank){
    //物理量用の瓶の設定
    double M[Set_of_Bins],X[Set_of_Bins],g[Set_of_Bins],E[Set_of_Bins],C[Set_of_Bins],sM[Set_of_Bins],sX[Set_of_Bins],sg[Set_of_Bins];
    RK4_KPoint_Set();
    
    #pragma omp parallel num_threads(THREADS)
    {
        sfmt_t sfmt;
        sfmt_init_gen_rand(&sfmt, (unsigned int)time(NULL)+omp_get_thread_num()+myrank*100);
        //printf("%d %lf\n",omp_get_thread_num(),sfmt_genrand_real2(&sfmt));
        
        //初期緩和
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);
        int j;
        for (j=0; j<100; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        LLG_Relaxation(Data_Interval,&sfmt);
        #pragma omp master
        {Replica_Exchange(j,&sfmt);}
        }
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);

        for (j=0; j<100; j++){
        Repetitive_MC_Step(tmax_Interval,&sfmt);
        LLG_Relaxation(Data_Interval,&sfmt);
        #pragma omp master
        {Replica_Exchange(j,&sfmt);}
        }
        Repetitive_MC_Step(Initial_Relaxation,&sfmt);
        
        //物理量の測定
        int i;
        for (i=0; i<Set_of_Bins; i++) {
            Repetitive_MC_Step(tmax_Interval,&sfmt);
            LLG_Relaxation(Data_Interval,&sfmt);
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
    printf("END %d\n",myrank);
    MPI_Barrier(MPI_COMM_WORLD);
    if (myrank==0){
                printf("Gather\n");
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
#endif
