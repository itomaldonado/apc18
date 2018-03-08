#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

/* #define ndata 1000 */
#define ndata 1000000

int main(int argc, char *argv[])
{

    int me, nprocs, i = 0, left, right;
    MPI_Status status;
    //MPI_Request request;

    float a[ndata];
    float b[ndata];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    /* Initialize data */
    for (i = 0; i < ndata; ++i)
    {
        a[i] = me;
        b[i] = -1;
    }
    /* Compute neighbour ranks */
    right = (me + 1) % nprocs;
    left = (me - 1 + nprocs) % nprocs;
    
    /* odd number ranks receive first, even number ranks send first: Sendrecv data */
    if (me % 2) {
        MPI_Recv(b, ndata, MPI_REAL, left, 0, MPI_COMM_WORLD, &status);
        MPI_Send(a, ndata, MPI_REAL, right, 0, MPI_COMM_WORLD);
    } else {
        MPI_Send(a, ndata, MPI_REAL, right, 0, MPI_COMM_WORLD);
        MPI_Recv(b, ndata, MPI_REAL, left, 0, MPI_COMM_WORLD, &status);
    }

    printf("\tI am task %d and I have received b(0) = %1.2f \n", me, b[0]);

    MPI_Finalize();
    return 0;
}