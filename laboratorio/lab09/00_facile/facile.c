#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#define NUM_THREADS 10

void *func(void *arg)
{
    sleep(2);
    printf("%f \n", *((double *)arg));
    free(arg);
    pthread_exit(NULL);
}

int main()
{

    pthread_t tid;
    int i;
    double *value;

    for (i = 0; i < NUM_THREADS; i++)
    {
        value = (double *)malloc(sizeof(double));
        *value = (double)rand();
        pthread_create(&tid, NULL, func, (void *)value);
    }

    pthread_exit(NULL);
}
