CC = nvcc
CFLAGS = 

.PHONY=ex1 ex2 ex3

TARGETS = ex1 ex2 ex3

all: $(TARGETS)


ex1.o:
	$(CC) $(CFLAGS) -c ex1.cu

ex1: ex1.o
	$(CC) $(CFLAGS) -o ex1 ex1.o

ex2.o:
	$(CC) $(CFLAGS) -c ex2.cu

ex2: ex2.o
	$(CC) $(CFLAGS) -o ex2 ex2.o

ex3.o:
	$(CC) $(CFLAGS) -c ex3.cu

ex3: ex3.o
	$(CC) $(CFLAGS) -o ex3 ex3.o

clean:
	rm -f *.o $(TARGETS) *.stdout *.txt *.out $(TARGETS)

