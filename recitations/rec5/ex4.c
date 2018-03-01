#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int numnodes, myid, mpi_err;
#define mpi_root 0

/* each processor will get COUNT elements from the root */
#define COUNT 10

/*
! This program shows how to use MPI_Scatter and MPI_Reduce
! Each processor gets different data from the root processor
! by way of mpi_scatter.  The data is summed and then sent back
! to the root processor using MPI_Reduce.  The root processor
! then prints the global sum. 
*/
int main(int argc, char *argv[])
{
  int *myray, *send_ray, *back_ray;
  int count;
  int size, mysize, i, k, j, total, gtotal;
  mpi_err = MPI_Init(argc, argv);
  mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
  mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &myid);


  mpi_err = MPI_Finalize();
  return 0;
}
