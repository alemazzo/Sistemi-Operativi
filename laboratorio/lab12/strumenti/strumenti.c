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

pthread_mutex_t mutexThread = PTHREAD_MUTEX_INITIALIZER;
int numThread = 0;

void *Thread(void *args)
{
    int rc;
    pthread_t tid;
    const char *Label = "Thread";

    DBGpthread_mutex_lock(&mutexThread, Label);

    printf("Num Thread = %d\n", numThread);
    fflush(stdout);

    DBGpthread_mutex_unlock(&mutexThread, Label);

    while (1)
    {
        sleep(1);
        DBGpthread_mutex_lock(&mutexThread, Label);

        if (numThread == 5)
        {
            printf("Non posso creare un altro thread - termino");
            numThread--;
            DBGpthread_mutex_unlock(&mutexThread, Label);
            pthread_exit(NULL);
        }
        else
        {
            rc = pthread_create(&tid, NULL, Thread, NULL);
            if (rc)
            {
                printf("Error creating pthread -> exit()");
                exit(1);
            }
            else
                numThread++;
        }

        DBGpthread_mutex_unlock(&mutexThread, Label);
    }
}

int main(int argc, char *argv[])
{
    int rc;
    pthread_t tid;

    while (1)
    {
        DBGpthread_mutex_lock(&mutexThread, "Main");

        rc = pthread_create(&tid, NULL, Thread, NULL);
        if (rc)
        {
            printf("Error creating pthread -> exit()");
            exit(1);
        }
        else
            numThread++;

        DBGpthread_mutex_unlock(&mutexThread, "Main");
        sleep(5);
    }
}
