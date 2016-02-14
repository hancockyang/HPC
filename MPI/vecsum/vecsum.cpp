#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]){
 
    int i, myid,numprocs,q;
	int loc_n,root;
    double sum,totsum;
	double startwtime, endwtime;
	MPI_Status status;

    int n = 10000;	            //size of the array
    double * p1;
    double sendbuff[60000], loc_p[60000]; 
	p1 = new double[n]; 

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	loc_n = n/numprocs;

	//printf("Process %10.5f on \n", myid);
        //printf("loc_n%5d",loc_n);
	if (myid == 0) 
	{
		// generate a ramdom array p1[n]
		//srand(time(NULL));
		for (i = 0; i < n; i++)
		{
		    //p1[i] = rand()%100+1;
		    p1[i] = i+1;
		    //printf("%10.5f",p1[i]);
		}
                //printf("\n");
		
                // send the frist loc_n to 0
		startwtime = MPI_Wtime();
                for (i = 0; i < loc_n; i++)
                    loc_p[i] = p1[i];

		for (q = 1; q < numprocs; q++)
		{
			for (i = 0; i < loc_n; i++)
                            sendbuff[i] = p1[loc_n*q+i];
			MPI_Send(&sendbuff, loc_n, MPI_DOUBLE, q, 0, MPI_COMM_WORLD);
		}
 	} 
	else 
	{
            MPI_Recv(&loc_p, loc_n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }
	totsum = 0.0;
	sum = 0.0;
	for (i = 0; i < loc_n; i ++) 
		sum += loc_p[i];
        //printf("Sum of process %5d is: %16.5f\n",myid,sum);
	MPI_Reduce(&sum, &totsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myid == 0) 
	{
		endwtime = MPI_Wtime();
		printf("\nThe sum of 1 to %d is %f\n", n, totsum);
		printf("wall clock time = %f\n", endwtime-startwtime);
	}
	MPI_Finalize();

    return 0;
}
