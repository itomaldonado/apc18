#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


int main(int argc, char* argv)
{
    int myid, numprocs;
    int tag,source,destination,count;
    double buffer;
 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    /* Write your code here */
    
    MPI_Finalize();
}
