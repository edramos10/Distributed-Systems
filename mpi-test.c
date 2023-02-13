    #include <mpi.h>
    #include <stdio.h>
    int main (int nargs, char* args[])
    {
    int numprocs, my_rank;
    //   MPI initializations
    MPI_Init (&nargs, &args);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    printf("Hello world, I have  rank %d out of %d \n" ,my_rank,numprocs);
    //  End MPI
    MPI_Finalize ();

    return 0;
    }