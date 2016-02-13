
#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]){
	double startTracked = omp_get_wtime();
	printf("Static:\n");
	#pragma omp parallel
	{
		 #pragma omp for schedule(static) nowait
		 for(int idx = 0 ; idx < 10 ; ++idx){
			  printf("[%2.2lf]I am %d working on %d\n",omp_get_wtime()-startTracked,omp_get_thread_num(),idx);
			  const double overTime = omp_get_wtime() + idx;
			  while(omp_get_wtime() < overTime);
		 }
		 printf("[%2.2lf]I am %d it is over for me!\n",omp_get_wtime()-startTracked,omp_get_thread_num());
	}
	double endTracked = omp_get_wtime();
	printf("Total Time Static  = %lf s\n", (endTracked-startTracked));
	startTracked = omp_get_wtime();
	printf("Dynamic:\n");
	#pragma omp parallel
	{
		 #pragma omp for schedule(dynamic) nowait
		 for(int idx = 0 ; idx < 10 ; ++idx){
			  printf("[%2.2lf]I am %d working on %d\n",omp_get_wtime()-startTracked,omp_get_thread_num(),idx);
			  const double overTime = omp_get_wtime() + idx;
			  while(omp_get_wtime() < overTime);
		 }
		 printf("[%2.2lf]I am %d it is over for me!\n",omp_get_wtime()-startTracked,omp_get_thread_num());
	}

	endTracked = omp_get_wtime();
	printf("Total Time Dynamic  = %lf s\n", (endTracked-startTracked));

	system("pause");
	return 0;
}