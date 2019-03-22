//srun -n 6 ./pi_mpi
//Pi is 3.14159265358979340

#include<stdio.h>
#include<math.h>
#include<mpi.h>
#define INTERVALS 5000000000L

int main(int argc, char *argv[]){
  long double area = 0.0;
  long double xi;
  long i;
  int myrank,nprocs;
  long double pi;

  //Initialization
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

  //To calculate the a part of pi for each process
  for (i=myrank*1.0; i<INTERVALS; i+=nprocs*1.0) {
    xi=(1.0L/INTERVALS)*(i+0.5L);
    area += 4.0L/(INTERVALS*(1.0L+xi*xi));
  }

  //To gather the results from all processes
  MPI_Reduce(&area,&pi,1,MPI_LONG_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(myrank==0){
	  printf("Pi is %20.17Lf\n", pi);
  }
  
  fflush(stdout);
  MPI_Finalize();
  return 0;

}



