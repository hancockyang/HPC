#include <stdio.h> 
#include <mpi.h>
//#include <iostream>
int main (int argc, char *argv[]) { 
	int token, NP, myrank; 
	MPI_Status status; 

	MPI_Init (&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &NP); 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 
	if (myrank != 0) { 
		 // Everyone except master receives from processor 1 less than its own rank
		 MPI_Recv(&token, 1, MPI_INT, myrank - 1, 0, MPI_COMM_WORLD, &status); 
		 printf("Process %d received token %d from process %d\n", myrank, token, myrank - 1); 
	}
	else{
		 // Master sets initial value before sending. 
		token = -1; 

	}
	token += 2; 
	MPI_Send(&token, 1, MPI_INT, (myrank + 1) % NP, 0, MPI_COMM_WORLD); 
	// Now process 0 can receive from the last process. 
	if (myrank == 0) { 
		MPI_Recv(&token, 1, MPI_INT, NP - 1, 0, MPI_COMM_WORLD, &status); 
		printf("Process %d received token %d from process %d\n", myrank, token, NP - 1); 
	}
	MPI_Finalize(); 
	//system("pause");
}