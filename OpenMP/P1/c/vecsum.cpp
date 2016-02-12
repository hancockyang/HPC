#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int main(int argc, char *argv[]){
 
    time_t start, finish; 
 
    int i, tid;
    int totsum;

    int n = 2000;	            //size of the array
    int *p1 = new int[n];
    //omp_set_num_threads(4);
    int ncore = omp_get_num_procs();    // no. of processor
    int nthread = omp_get_num_threads(); 
    for (i = 0; i < n; i++){p1[i] = i+1;}
    printf("\n");

	cout<<"number of processors: "<< ncore<<endl;
	cout<<"number of threads: "<< nthread<<endl;
    // reduction sum
    totsum = 0.0;
    start = clock();
    #pragma omp parallel for reduction(+:totsum)
    for ( int j = 0; j < n; j++) 
        totsum += p1[j];  
    finish = clock();    
    printf("\nTotal sum from 1 to %d = %i\n",n,totsum);
    printf("Time of reduction = %ld ms\n",finish-start);
    system("pause");
    return 0;
}
