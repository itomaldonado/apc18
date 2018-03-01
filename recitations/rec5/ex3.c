#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define N 60

int main(int argc, char *argv[])
{
    int i, my_id, num_procs, num_elem;
    int array[N], array_final[N];
    int *array_recv;

    MPI_Init(&argc, &argv);                    /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);     /* get current process id */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); /* get number of processes */

    // Write the code to complete the exercise below.


    MPI_Finalize();
    return 0;
}