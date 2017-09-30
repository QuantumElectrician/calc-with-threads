//
//  main.c
//  calc_with_threads
//
//  Created by Владислав Агафонов on 30.09.2017.
//  Copyright © 2017 Владислав Агафонов. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int begin;
    int end;
    int result;
}threadTask;

static int calc() {
    
    return calc();
}

int main(int argc, const char * argv[])
{
    int result;
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    int NUMBER_OF_THREADS = atoi(argv[3]);
    unsigned long sigma = 0;

    threadTask* tasks = malloc(NUMBER_OF_THREADS * sizeof(threadTask));
    pthread_t* threadId = malloc(NUMBER_OF_THREADS* sizeof(pthread_t));
    
    int loadPerThread = (right - left) / NUMBER_OF_THREADS;
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        tasks[i].begin = left + i * loadPerThread;
        tasks[i].end = tasks[i].begin + loadPerThread;
        result = pthread_create(threadId+i, NULL, calc(), (void*) &tasks[i]);
        if (result)
        {
            printf("Can't create thread %d, returned value = %d\n", i,result);
            exit(-1);
        }
    }
    
    int delta = right - left + loadPerThread * NUMBER_OF_THREADS;
    for (int i = delta; i <= right; i++)
    {
        sigma = sigma + delta;
    }
    
    return 0;
}
