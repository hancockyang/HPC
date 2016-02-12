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
    double totsum;

    int n = 10;	            //size of the array
    int *p1 = new int[n];
    
    int ncore = omp_get_num_procs();    // no. of processor
    //int *sum  = new int[ncore];


    // generate a ramdom array p1[n]
    //srand(time(NULL));
    for (i = 0; i < n; i++){p1[i] = i+1;}
    printf("\n");
    
    // parallel
    totsum = 0.0;
    start = clock();
    #pragma omp parallel for private(tid) 
    for ( int j = 0; j < ncore; j++) 
    {
        tid = omp_get_thread_num(); 
        int istart = tid*n/ncore;
        int iend  = (tid+1)*n/ncore;
        int sum = 0;
        for (int k=istart;k<iend;k++)
            sum += p1[k];
        printf("sum of threads %5i = %i\n",tid,sum);    
        
        #pragma omp atomic
        totsum += sum;
    }
    finish = clock();
	cout<<"Total sum from 1 to "<<n<<" = "<<totsum<<endl;
    //printf("Total sum from 1 to %i = %2i \n",n,totsum);
    printf("Time of parallel = %ld ms \n",finish-start);
    
    system("pause");
    return 0;
}
