CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
LINKS = -lm

pi_mpi: pi_mpi.c
	$(MPICC) -o pi_mpi pi_mpi.c $(LINKS)

clean: 
	rm -f pi_mpi *~ a.out
