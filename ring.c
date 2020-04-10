/*
 * A template for the 2016 MPI lab at the University of Warsaw.
 * Copyright (C) 2016, Konrad Iwanicki
 * Further modifications by Krzysztof Rzadca 2018
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
    
    int numProcesses, myRank;

    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
    int val;
    int nextNode = (myRank + 1) % numProcesses;
    switch(myRank){
        case 0:
            val = 1;
//            printf("%3d to %3d sending %d\n", myRank, nextNode,  val);
            MPI_Send(&val, 1, MPI_INT, nextNode, 0, MPI_COMM_WORLD);
            MPI_Recv(&val, 1, MPI_INT, numProcesses - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("recieved %d\n", val);
            break;
        default:
            //recieve
            MPI_Recv(&val, 1, MPI_INT, myRank -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            val *= myRank;
            //send forward
            MPI_Send(&val, 1, MPI_INT, (myRank + 1) % numProcesses, 0, MPI_COMM_WORLD);
    }

    
    MPI_Finalize(); /* mark that we've finished communicating */
    
    return 0;
}

