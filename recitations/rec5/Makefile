CC = icpc
MPCC = mpicc
OPENMP = -openmp
CFLAGS = -Wall -O3
LIBS =

all: ex1 ex2.1 ex2.2 ex3 ex4

ex1.o: ex1.c
	$(MPCC) -c $(CFLAGS) ex1.c

ex1: ex1.o
	$(MPCC) -o ex1 ex1.o

ex2.1.o: ex2.1.c
	$(MPCC) -c $(CFLAGS) ex2.1.c

ex2.1: ex2.1.o
	$(MPCC) -o ex2.1 ex2.1.o

ex2.2.o: ex2.2.c
	$(MPCC) -c $(CFLAGS) ex2.2.c

ex2.2: ex2.2.o
	$(MPCC) -o ex2.2 ex2.2.o

ex3.o: ex3.c
	$(MPCC) -c $(CFLAGS) ex3.c

ex3: ex3.o
	$(MPCC) -o ex3 ex3.o

ex4.o: ex4.c
	$(MPCC) -c $(CFLAGS) ex4.c

ex4: ex4.o
	$(MPCC) -o ex4 ex4.o

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt

