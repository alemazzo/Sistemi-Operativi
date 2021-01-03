/* banale_quasigiusto.c  */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
#ifndef _REENTRANT
#define _REENTRANT
#endif

#ifdef _POSIX_C_SOURCE
#if _POSIX_C_SOURCE < 200112L
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
#else
#define _POSIX_C_SOURCE 200112L
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
/* per uintptr_t */
#include <stdint.h>
/* PRIiPTR */
#include <inttypes.h>
/* per strerror_r */
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 1000

void *PrintHello(void *arg)
{
    printf("index %" PRIuPTR "\n", (uintptr_t)arg);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc, t, *p;
    uintptr_t t0 = 0;

    while (1)
    {

        for (t = 0; t < NUM_THREADS; t0++, t++)
        {
            printf("Creating thread %" PRIuPTR "\n", t0);
            rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t0);
            if (rc)
            {
                char msg[100];
                strerror_r(rc, msg, 100);
                printf("pthread_create failed : %s\n", msg);
                exit(1);
            }
        }

        for (t = 0; t < NUM_THREADS; t++)
        {
            rc = pthread_join(threads[t], (void **)&p);
            if (rc)
            {
                char msg[100];
                strerror_r(rc, msg, 100);
                printf("pthread_join failed : %s\n", msg);
                exit(1);
            }
        }
    }

    printf("fine main\n");
    fflush(stdout);

    pthread_exit(NULL); /* anche qui ho tolto il commento */
    return (0);
}
