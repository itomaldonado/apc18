# Recitation 5: MPI

## Team:

## Exercises:

### EX1

### EX2.1

Deadlock is encountered when process 0 tries to send and receive data from another
process. All of the other processes simply call MPI_Recv (receiving from their neighboring lower process) 
and then MPI_Send (sending the value to their neighboring higher process) to pass the value along the ring. 
MPI_Send and MPI_Recv will block until the message has been transmitted. We fix this by allowing all
other processes to finish receiving messages and finally permitting process 0 to receive its message
from the last process. 

### EX2.2.

MPI_Isend and MPI_Irecv are non-blocking, meaning that the function
call returns before the communication is completed. Deadlock then
becomes impossible with non-blocking communication, but other
precautions must be taken in order to ensure that data is received properly.
Placing an MPI_Wait call for each send and receive call ensures that the 
process receives/sends before advancing the program. The MPI_Request
will stall until MPI_Wait call is completed. 


### EX3

### EX4
