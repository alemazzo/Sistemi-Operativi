#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* PRIiPTR */
#include <inttypes.h>
#include <pthread.h>

void *func(void *arg)
{
    int rc;
    pthread_t tid;
    intptr_t index = (intptr_t)arg;

    usleep(1000);
    printf("Indice : %" PRIiPTR "\n", index);

    rc = pthread_create(&tid, NULL, func, (void *)(index + 1));
    if (rc)
    {
        printf("pthread_create() failed: error %i\n", rc);
        exit(1);
    }

    rc = pthread_join(tid, NULL);
    if (rc)
    {
        printf("pthread_join() failed: error %i\n", rc);
        exit(1);
    }

    pthread_exit(NULL);
}

int main()
{
    int rc;
    pthread_t tid;
    intptr_t index = 0;

    printf("Indice : %" PRIiPTR "\n", index);

    rc = pthread_create(&tid, NULL, func, (void *)(index + 1));
    if (rc)
    {
        printf("pthread_create() failed: error %i\n", rc);
        exit(1);
    }

    rc = pthread_join(tid, NULL);
    if (rc)
    {
        printf("pthread_join() failed: error %i\n", rc);
        exit(1);
    }

    pthread_exit(NULL);
}
