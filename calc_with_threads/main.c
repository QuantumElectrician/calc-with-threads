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

void* calc(threadTask* threadTaskAd)
{
    threadTaskAd->result = 0;
    int k = threadTaskAd->begin;
    while (k != threadTaskAd->end)
    {
        threadTaskAd->result = threadTaskAd->result + k;
        k++;
    }
    return threadTaskAd;
}

int main(int argc, const char * argv[])
{
    int result;
    int left = atoi(argv[1]);
    int right = atoi(argv[2]);
    int NUMBER_OF_THREADS = atoi(argv[3]);
    unsigned long sigma = 0;

    threadTask* tasks = (threadTask*)malloc(NUMBER_OF_THREADS * sizeof(threadTask));
    pthread_t* threadId = malloc(NUMBER_OF_THREADS* sizeof(pthread_t));
    
    int loadPerThread = (right - left) / NUMBER_OF_THREADS;
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        tasks[i].begin = left + i * loadPerThread;
        tasks[i].end = tasks[i].begin + loadPerThread;
        result = pthread_create(threadId+i, NULL, calc, (threadTask*)&tasks[i]);
        if (result)
        {
            printf("Can't create thread %d, returned value = %d\n", i,result);
            exit(-1);
        }
    }
    
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threadId[i], NULL);
        sigma = sigma + tasks[i].result;
    }
    
    int delta = left + loadPerThread * NUMBER_OF_THREADS;
    for (int i = delta; i <= right; i++)
    {
        sigma = sigma + i;
    }
    
    free(tasks);
    free(threadId);
    printf("%lu\n", sigma);
    return 0;
}
