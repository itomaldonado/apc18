CC := gcc

ifeq ($(DEBUG),1)
	CFLAGS := -Wall -O0 -g
else
	CFLAGS := -Wall -O1 -DNDEBUG 
endif

LDFLAGS := -lrt

all: sizes pointer swap isort

sizes.o: sizes.c
	$(CC) $(CFLAGS) -c sizes.c

sizes: sizes.o
	$(CC) -o sizes sizes.o $(LDFLAGS)

pointer.o: pointer.c
	$(CC) $(CFLAGS) -c pointer.c

pointer: pointer.o
	$(CC) -o pointer pointer.o $(LDFLAGS)

swap.o: swap.c
	$(CC) $(CFLAGS) -c swap.c

swap: swap.o
	$(CC) -o swap swap.o $(LDFLAGS)

isort.o: isort.c 
	$(CC) -Wall -O1 -DNDEBUG -c -gdwarf-3 isort.c 

isort: isort.o
	$(CC) -gdwarf-3 -o isort isort.o $(LDFLAGS)

clean:
	rm -f sizes pointer swap isort *.o
