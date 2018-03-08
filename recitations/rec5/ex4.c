#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int numnodes, myid, mpi_err;
#define mpi_root 0

/* each processor will get COUNT elements from the root */
#define COUNT 10

/* Number of elements */
#define N 60

/*
! This program shows how to use MPI_Scatter and MPI_Reduce
! Each processor gets different data from the root processor
! by way of mpi_scatter.  The data is summed and then sent back
! to the root processor using MPI_Reduce.  The root processor
! then prints the global sum. 
*/
int main(int argc, char *argv[])
{
    int array[N];
    int size, i, total, gtotal, sum;
    int *array_recv, *offsets, *counts;

    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Only root does this
    if (myid == 0) { 
        
        // initialize array:
        for(i = 0; i < N; i++) {
            array[i] = i;
        }
    }

    // Scatter array
    offsets = (int *)malloc(numnodes*sizeof(int));
    counts = (int *)malloc(numnodes*sizeof(int));

    // get counts for each rank
    for (i=0; i < numnodes; ++i) { 
        counts[i] = N / numnodes;
    }
    for (i = 0; i < N % numnodes; i++){
        // add one to each rank until we use the reminder
        counts[i] += 1;
    }

    // get the offsets of each rank
    sum = 0;
    for (i = 0; i < numnodes; i++) {
        offsets[i] = sum;
        sum += counts[i];
    }

    array_recv = (int *)malloc(sizeof(int) * counts[myid]);
    MPI_Scatterv(&array, counts, offsets, MPI_INT, array_recv, counts[myid], MPI_INT, 0, MPI_COMM_WORLD);


    // Overwrite array with rank id
    total = 0;
    for(i = 0; i < counts[myid]; i++) {
        total += array_recv[i];
    }

    printf("Rank: %d -- Local sum total: %d.\n", myid, total);

    // Reduce all of the local sums into the global sum
    MPI_Reduce(&total, &gtotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if (myid == 0) {
        printf("Global sum total: %d.\n", gtotal);
    }

    // clean up
    free(array_recv);
    free(offsets);
    free(counts);

    // finalize
    MPI_Barrier(MPI_COMM_WORLD);
    mpi_err = MPI_Finalize();
    return 0;
}
