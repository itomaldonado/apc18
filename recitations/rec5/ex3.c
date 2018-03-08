#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define N 60

int main(int argc, char *argv[])
{
    int i, my_id, num_procs, sum;
    //int num_elem;
    int array[N], array_final[N];
    int *array_recv, *offsets, *counts; 

    MPI_Init(&argc, &argv);                    /* starts MPI */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);     /* get current process id */
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); /* get number of processes */

    // Write the code to complete the exercise below.
    //num_elem = (N / num_procs);

    // Only root does this
    if (my_id == 0) { 
        // initialize array:
        for(i = 0; i < N; i++) {
            array[i] = i;
        }
    }

    // Scatter array
    offsets = (int *)malloc(num_procs*sizeof(int));
    counts = (int *)malloc(num_procs*sizeof(int));

    // get counts for each rank
    for (i=0; i < num_procs; ++i) { 
        counts[i] = N / num_procs;
    }
    for (i = 0; i < N % num_procs; i++){
        // add one to each rank until we use the reminder
        counts[i] += 1;
    }

    // get the offsets of each rank
    sum = 0;
    for (i = 0; i < num_procs; i++) {
        offsets[i] = sum;
        sum += counts[i];
    }

    array_recv = (int *)malloc(sizeof(int) * counts[my_id]);
    MPI_Scatterv(&array, counts, offsets, MPI_INT, array_recv, counts[my_id], MPI_INT, 0, MPI_COMM_WORLD);
    
    //MPI_Scatter(&array, num_elem, MPI_INT, array_recv, num_elem, MPI_INT, 0, MPI_COMM_WORLD);

    // Overwrite array with rank id
    for(i = 0; i < counts[my_id]; i++) {
        array_recv[i] = my_id;
    }

    // Gather data
    MPI_Gatherv(array_recv, counts[my_id], MPI_INT, &array_final, counts, offsets, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Gather(array_recv, num_elem, MPI_INT, &array_final, num_elem, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_id == 0) {
        for(i = 0; i < N;i++) {
            printf("Value %d was processed by rank %d\n", i, array_final[i]);
        }
    }

    // clean up
    free(array_recv);
    free(offsets);
    free(counts);

    // finalize
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}