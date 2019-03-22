CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
LINKS = -lm

pingpong: pingpong.c
	$(MPICC) -o pingpong pingpong.c $(LINKS)

clean: 
	rm -f pingpong *~ a.out
