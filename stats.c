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

int main(int argc, char * argv[])
{


    MPI_Init(&argc,&argv); /* intialize the library with parameters caught by the runtime */

    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    srand(spec.tv_nsec); // use nsec to have a different value across different processes

    unsigned t = rand() % 5;

    int numProcesses, myRank;

    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    double startTime;

    double endTime;

    double executionTime;

    int * val[100];

    startTime = MPI_Wtime();

    switch (myRank){
        case 0:
            MPI_Send(val, 100, MPI_INT, 1, 0, MPI_COMM_WORLD);
            break;
        case 1:
            MPI_Recv(val, 100, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            break;
    }
    endTime = MPI_Wtime();

    executionTime = endTime - startTime;

    printf("%d/%d duration: %f\n", myRank, numProcesses, executionTime);

    MPI_Finalize(); /* mark that we've finished communicating */

    return 0;
}