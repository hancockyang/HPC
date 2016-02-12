#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]){
 
    time_t start, finish; 
    double dt;
 
    int i, j, tid;
    double  totsum, sum;
    int  n = 2000000;	            //size of the array
    double *p1 = new double[n];
    
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
    dt = (double)(finish - start);
    printf("Total sum = %e\n",totsum);
    printf("Time of sequential = %e ms\n\n",dt);
    
    // parallel
    totsum = 0.0;
    start = clock();
    #pragma omp parallel private(i, sum) shared(p1)
    {
        sum = 0.0;
        #pragma omp for schedule(static) nowait
        for ( j = 0; j < n; j++) 
            sum += p1[j];
        #pragma omp atomic
            totsum += sum;
        printf("sum of threads %5d = %i\n",omp_get_thread_num(),sum); 
    }
    finish = clock();
    dt = (double)(finish - start);
    printf("\nTotal sum = %e\n",totsum);
    printf("Time of parallel = %e ms\n",dt);
    
    // reduction sum
    totsum = 0.0;
    start = clock();
    #pragma omp parallel for private(j) shared(p1) schedule(static) reduction(+:totsum)
    for ( j = 0; j < n; j++) 
        totsum += p1[j];  
    finish = clock();    
    dt = (double)(finish - start) ;
    printf("\nTotal sum = %e\n",totsum);
    printf("Time of reduction = %e ms\n",dt);
    system("pause");
    return 0;
}
