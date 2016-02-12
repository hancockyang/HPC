//
//  main.cpp
//  new
//
//  Created by hankang yang on 2/11/16.
//  Copyright © 2016 hankang yang. All rights reserved.
//
#include <iostream>
#include <libiomp/omp.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

int main(int argc, char *argv[]){
    
    time_t start, finish;
    
    int i;
    double totsum;
    
    int n = 10;              //size of the array
    int *p1 = new int[n];
    
    for (i = 0; i < n; i++)
    {
        p1[i] = i+1;
        
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
    
    return 0;
}