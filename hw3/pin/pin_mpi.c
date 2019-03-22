//The PIN is 2572 (nprocs = 40, time = 2.497429 sec.)
//
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<assert.h>
#include<math.h>


int main(int argc, char* argv[]){
int nprocs;
int myrank;
int result=0;
double time_start,time_end,time_total,time_temp;
int fun_g=0;

assert(argc==2);
double stop=(double)atoi(argv[1]);

//Initialization
assert(stop >=1.0);
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

time_start=MPI_Wtime();

//formula
for(double x=myrank*1.0;x<stop;x+=nprocs*1.0){
double tmp=sin(x);
double tmp2=tmp*tmp;
int z=(int)(tmp2*10000.0);
fun_g = (fun_g+z)%10000;
}
time_end=MPI_Wtime();
time_total=time_end-time_start;

//To gather the results from all processes
//Both PIN number and running time
MPI_Reduce(&fun_g,&result,1,MPI_INT, MPI_SUM, 0 , MPI_COMM_WORLD);
MPI_Reduce(&time_total,&time_temp,1,MPI_DOUBLE, MPI_SUM,0,MPI_COMM_WORLD);
result = result%10000;


//print results to the terminal
if(myrank==0){
	printf("The PIN is %d (nprocs = %d, time = %f sec.)\n",result,nprocs,time_temp);
	}

fflush(stdout);
MPI_Finalize();
return 0;
}
