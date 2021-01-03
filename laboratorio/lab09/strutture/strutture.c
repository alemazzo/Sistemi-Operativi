
#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 2

typedef struct s
{
    int threads_to_create;
    int thread_index;
    char str[100];
} Struttura;

void *t_func(void *args)
{
    int i, res;
    Struttura *s;
    Struttura *result;
    pthread_t *threads;

    sleep(1);

    s = (Struttura *)args;
    threads = (pthread_t *)malloc(sizeof(pthread_t) * s->threads_to_create);
    for (i = 0; i < s->threads_to_create; i++)
    {
        Struttura *s2 = (Struttura *)malloc(sizeof(Struttura));
        s2->threads_to_create = s->threads_to_create - 1;
        s2->thread_index = i;
        res = pthread_create(&threads[i], NULL, t_func, (void *)s2);
        if (res)
        {
            char msg[100];
            strerror_r(res, msg, 100);
            printf("Error from pthread_create() : %s \n", msg);
            exit(1);
        }
    }

    for (i = 0; i < s->threads_to_create; i++)
    {

        res = pthread_join(threads[i], (void **)&result);
        if (res)
        {
            char msg[100];
            strerror_r(res, msg, 100);
            printf("Error from pthread_join() : %s \n", msg);
            exit(1);
        }
        printf("%s\n", result->str);
        free(result);
    }

    sprintf(s->str, "%d %d", s->threads_to_create, s->thread_index);
    pthread_exit((void *)s);
}

int main()
{
    pthread_t tid;
    int i, res;
    for (i = 0; i < NUM_THREAD; i++)
    {
        Struttura *s = (Struttura *)malloc(sizeof(Struttura));
        s->threads_to_create = 3;
        s->thread_index = i;
        res = pthread_create(&tid, NULL, t_func, (void *)s);
        if (res)
        {
            char msg[100];
            strerror_r(res, msg, 100);
            printf("Error from pthread_create() : %s \n", msg);
            exit(1);
        }
    }

    pthread_exit(NULL);
}