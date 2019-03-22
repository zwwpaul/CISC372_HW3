#include<stdio.h>
#include<mpi.h>

#define NPINGS 1000000
#define SMALL 100
//To make messages with 0 bytes
char message[SMALL];

//To compute the communication time between two objects
double pingpong_time(int ob1, int ob2,int npings, int myrank){
double time_s=MPI_Wtime();
if(myrank == ob1){
	for(int i=0;i<npings;i++){
		MPI_Send(&message,SMALL,MPI_BYTE,ob2,0,MPI_COMM_WORLD);
		MPI_Recv(&message,SMALL,MPI_BYTE,ob2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
}else if(myrank == ob2){
        for(int i=0;i<npings;i++){
                MPI_Recv(&message,SMALL,MPI_BYTE,ob1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        	MPI_Send(&message,SMALL,MPI_BYTE,ob1,0,MPI_COMM_WORLD);
	}
}
double time_e=MPI_Wtime();
double time_total=time_e-time_s;
return time_total;
}



int main(int argc, char*argv[]){
 int myrank,nprocs;
 double result;
 
 //Initialization
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
 MPI_Comm_size(MPI_COMM_WORLD,&nprocs);

 //If we have 40 processes, from 0 to 1 until 0 to 39 will be printed.

 for(int i=1; i<nprocs;i++){
	result =pingpong_time(0,i,NPINGS,myrank);
	//Different processes have different running time.
	//Until all processes reach the barrier (they're synchronized), print function will be executed.
	MPI_Barrier(MPI_COMM_WORLD);
	if (myrank==0){
		printf("Average time to transmit between 0 and %d: %11.10f\n",i,result/(2*NPINGS));
	}
 }
 fflush(stdout);
 MPI_Finalize();
 return 0;
}
