CC = icpc
MPCC = mpicc
OPENMP = -openmp
CFLAGS = -Wall -O3
LIBS =

all: ex1


ex1.o: ex1.c
	$(MPCC) -c $(CFLAGS) ex1.c

ex1: ex1.o
	$(MPCC) -o ex1 ex1.o

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt

