#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


int main(int argc, char* argv)
{
    int myid, numprocs;
    int tag,source,destination,count;
    double sendbuffer, recvbuffer;
    
    MPI_Request req = MPI_REQUEST_NULL;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    int number; 
    if (myid == 0){
       number = -1; 
       MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);
    }
    else if (myid == 1){ 
       MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
       printf("Process 1 received number %d from process 0\n", number);   
   }

   MPI_Cancel( &req );
   MPI_Wait( &req, MPI_STATUS_IGNORE);
   MPI_Wait( &req, MPI_STATUS_IGNORE);
   MPI_Finalize();
}
