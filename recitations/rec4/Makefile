CC = icpc
MPCC = mpicxx
OPENMP = -openmp
CFLAGS = -Wall -O3
LIBS =

# If you want to use gcc/g++ to compile the cpp files, you can also use
# the -fopenmp parameter to compile with OpenMP support.
# i.e. g++ -fopenmp helloworld.cpp -o helloworld 

all: helloworld matrix


helloworld.o: helloworld.cpp
	$(CC) -c $(OPENMP) $(CFLAGS) helloworld.cpp

helloworld: helloworld.o
	$(CC) -o helloworld $(OPENMP) helloworld.o

matrix.o: matrix.cpp
	$(CC) -c $(OPENMP) $(CFLAGS) matrix.cpp

matrix: matrix.o
	$(CC) -o matrix $(OPENMP) matrix.o

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt
