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

int getNodeId(){
    char name[MPI_MAX_PROCESSOR_NAME];
    int len;
    MPI_Get_processor_name(name, &len);
    return ((int) name[len-1]) % 2;
}

double measureLatency(int to, int payload){
    double startTime,endTime,executionTime;
    void * buff = (void*) malloc(payload);

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
    int node = getNodeId();
    int partnerNode = (node + 1) % 2;
    int partnerId = partnerNode * (numProcesses/2);

    printf("%d/%d partner: %d/%d\n", myRank, node, partnerId, partnerNode);

    MPI_Finalize(); /* mark that we've finished communicating */

    return 0;
}