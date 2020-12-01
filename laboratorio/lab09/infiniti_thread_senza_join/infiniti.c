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

#define NUM_THREADS 100000000

void *PrintHello(void *arg)
{
    printf("\nValue = %" PRIiPTR "\n", (intptr_t)arg);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int rc;
    intptr_t t;
    for (t = 0; t < NUM_THREADS; t++)
    {

        printf("Creating thread %" PRIiPTR "\n", t);
        rc = pthread_create(&tid, NULL, PrintHello, (void *)t);
        if (rc)
        {
            char msg[100];
            strerror_r(rc, msg, 100);
            printf("ERROR; return code from pthread_create() is %i \n", rc);
            printf("ERROR : %s\n", msg);
            exit(1);
        }
    }

    pthread_exit(NULL);
    return (0);
}
