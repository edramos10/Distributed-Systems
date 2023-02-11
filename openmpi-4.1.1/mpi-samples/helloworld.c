#include <stdio.h>
#include<mpi.h>
int main(int argc, char *argv[]){
    int mpierror, npes, myrank; 
    mpierror= MPI_Init(&argc , &argv);
    mpierror=MPI_Comm_size(MPI_COMM_WORLD, &npes);
    mpierror=MPI_Comm_rank( MPI_Comm comm , &myrank);

    printf("From process %d out of %d, Hello World!!!\n",myrank, npes);

    /*global instruction*/
    mpierror=MPI_Finalize();
    return 0;
}