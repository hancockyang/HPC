#include <stddef.h>
#include <stdlib.h>
#include <mpi.h>
#include <cstring>
#include <stdio.h>
//#include <iostream>
int main(int argc, char **argv ) 
{
	char message[30];
	int i,rank, size, type=99;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0) 
	{
		strcpy(message, "Hello world from Hankang Yang");
		for (i=1; i<size; i++)
			MPI_Send(message,30,MPI_CHAR,i,type,MPI_COMM_WORLD);
	} 
	else
		MPI_Recv(message,100,MPI_CHAR,0,type,MPI_COMM_WORLD,&status);
	printf( "Message from process =%d : %.30s\n", rank,message);
	MPI_Finalize();
	//system("pause");
	return 0;
}
