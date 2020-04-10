/*
 * A template for the 2016 MPI lab at the University of Warsaw.
 * Copyright (C) 2016, Konrad Iwanicki
 * Further modifications by Krzysztof Rzadca 2018
 * more changes kajetan boroszko on 10.04.2020.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

double measureLatency(void* buff, int to, int payload){
    double startTime,endTime,executionTime;

    startTime = MPI_Wtime();
    MPI_Send(buff, payload, MPI_BYTE, to, 0, MPI_COMM_WORLD);
    MPI_Recv(buff, payload, MPI_BYTE, to, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    endTime = MPI_Wtime();
    return endTime - startTime;
}


int main(int argc, char * argv[])
{


    MPI_Init(&argc,&argv); /* intialize the library with parameters caught by the runtime */

    int numProcesses, myRank;

    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int node = myRank/(numProcesses/2);
    int partnerNode, partnerRank;
    if(node == 0){
        partnerNode = 1;
        partnerRank = myRank + (numProcesses/2);
    } else {
        partnerNode = 0;
        partnerRank = myRank - (numProcesses/2);
    }

    printf("%d/%d on %d - partner %d on %d\n", myRank, numProcesses, node, partnerRank, partnerNode);fflush(stdout);

//    void * buff = malloc(100);
//    switch (node){
//        case 0: {
//            MPI_Recv(buff, 100, MPI_BYTE, partnerRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            MPI_Send(buff, 100, MPI_BYTE, partnerRank, 0, MPI_COMM_WORLD);
//            break;
//        }
//        case 1: {
//            double t = measureLatency(buff, partnerRank, 100);
//            printf("%2d %10d %f", myRank, 100, t);
//            break;
//        }
//    }
//
//    free(buff);

    MPI_Finalize(); /* mark that we've finished communicating */

    return 0;
}