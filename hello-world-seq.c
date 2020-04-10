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
    
    unsigned t = rand() % 5;
    sleep(t);
    
    int numProcesses, myRank;

    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    int len;
    char * name;

    MPI_Get_processor_name( name, len );
    
    printf("Hello world from %d/%d on ", myRank, numProcesses);

    for(int i=0; i<len; i++){
        printf("%c", name[i]);
    }
    printf("\n");
    
    MPI_Finalize(); /* mark that we've finished communicating */
    
    return 0;
}

