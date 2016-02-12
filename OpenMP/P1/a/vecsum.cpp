#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
 
    time_t start, finish; 
 
    int i, tid;
    double totsum;

    int n = 20000;	            //size of the array
    int *p1 = new int[n];
    
    int ncore = omp_get_num_procs();    // no. of processor
    //int *sum  = new int[ncore];


    // generate a ramdom array p1[n]
    //srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        //p1[i] = rand()%100+1;
        p1[i] = i+1;
        //printf("%5d",p1[i]);
    }
    printf("\n");
    
    // sequential
    totsum = 0.0;
    start = clock();
    for ( i = 0; i < n; i++)
        totsum += p1[i];
    finish = clock();    
    printf("Total sum from 1 to %8d = %8e\n",n,totsum);
    printf("Time of sequential = %ld ms\n",finish-start);

    system("pause");
    return 0;
	
}
