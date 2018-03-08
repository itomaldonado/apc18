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
    num_elem = (N / num_procs);

    // Only root does this
    if (my_id == 0) { 
        // initialize array:
        for(i = 0; i < N; i++) {
            array[i] = i;
        }
    }

    // Scatter array
    array_recv = (int *)malloc(sizeof(int) * num_elem);
    MPI_Scatter(&array, num_elem, MPI_INT, array_recv, num_elem, MPI_INT, 0, MPI_COMM_WORLD);

    // Overwrite array with rank id
    for(i = 0; i < num_elem; i++) {
        array_recv[i] = my_id;
    }

    // Gather data
    int *sub_avgs = NULL;
    if (my_id == 0) {
        MPI_Gather(array_recv, num_elem, MPI_INT, &array_final, num_elem, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Gather(array_recv, num_elem, MPI_INT, NULL, num_elem, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (my_id == 0) {
        for(i = 0; i < N;i++) {
            printf("Value %d was processed by rank %d", i, array_final[i]);
        }
    }

    // clean up
    free(array_recv);

    // finalize
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}