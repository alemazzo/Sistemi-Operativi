/* con_trucco.c  */

/* messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/
#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
#ifndef _REENTRANT
#define _REENTRANT
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

int main()
{
    int rc, *p;
    intptr_t t;

    while (1)
    {
        pthread_t *tids = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS);
        for (t = 0; t < NUM_THREADS; t++)
        {

            printf("Creating thread %" PRIiPTR "\n", t);
            rc = pthread_create(&tids[t], NULL, PrintHello, (void *)t);
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
            rc = pthread_join(tids[t], (void **)&p);
            if (rc)
            {
                char msg[100];
                strerror_r(rc, msg, 100);
                printf("pthread_join failed : %s\n", msg);
                exit(1);
            }
        }

        free(tids);
    }

    pthread_exit(NULL);
    return (0);
}
