/* file:  figliare.c */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include "printerror.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUML1 2
#define NUML2 2
#define NUMSTRUMENTI 3

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex[NUMSTRUMENTI];

void *L1(void *args)
{
    const char * Label = "L1";
    printf("partito thread L1\n");
    while (1)
    {
        DBGpthread_mutex_lock(&m, Label);

        printf("%s Inizia lavoro L1\n", Label);

        printf("%s Prende strumento 1\n", Label);
        sleep(1);

        printf("%s Prende strumento 2\n", Label);
        sleep(2);

        printf("%s Prende strumento 3\n", Label);
        printf("%s Rilascia strumento 2\n", Label);
        sleep(2);

    
        DBGpthread_mutex_unlock(&m, Label);

        sleep(1);
    }
}
void *L2(void *args)
{
    const char * Label = "L2";
    printf("partito thread L2\n");
    while (1)
    {
        DBGpthread_mutex_lock(&m, Label);

        printf("%s Inizia lavoro L2\n", Label);

        printf("%s Prende strumento 3\n", Label);
        sleep(1);

        printf("%s Prende strumento 2\n", Label);
        sleep(2);

        printf("%s Prende strumento 1\n", Label);
        printf("%s Rilascia strumento 2\n", Label);
        sleep(2);

        DBGpthread_mutex_unlock(&m, Label);
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int rc, i;
    pthread_t tid;

    for (i = 0; i < NUMSTRUMENTI; i++)
        pthread_mutex_init(&mutex[i], NULL);

    for (i = 0; i < NUML1; i++)
    {
        rc = pthread_create(&tid, NULL, L1, NULL);
        if (rc)
        {
            printf("Errore crezione thread");
            exit(1);
        }
    }

    for (i = 0; i < NUML2; i++)
    {
        rc = pthread_create(&tid, NULL, L2, NULL);
        if (rc)
        {
            printf("Errore crezione thread");
            exit(1);
        }
    }

    pthread_exit(0);
}
