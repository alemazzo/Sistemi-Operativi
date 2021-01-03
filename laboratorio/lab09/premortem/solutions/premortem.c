/* premortem.c  */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
/* per usare usleep dpvrei definire il simbolo _BSD_SOURCE 
   che pero' e' stato recentemente deprecato, da un annetto
   Occorre al suo posto definire il simbolo _DEFAULT_SOURCE
*/
#define _DEFAULT_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s
{
    unsigned int indice;
    pthread_t tid;
} S;

void *func(void *arg)
{
    void *pret;
    int res;
    pthread_t tid;
    S *p1, *p = (S *)arg;

    printf("indice %d\n", p->indice);
    fflush(stdout);
    usleep(1000);

    p1 = malloc(sizeof(S));
    if (p1 == NULL)
    {
        perror("malloc failed");
        exit(1);
    }
    p1->indice = p->indice + 1;
    p1->tid = pthread_self();
    res = pthread_create(&tid, NULL, func, (void *)p1);
    if (res)
    {
        printf("pthread_create() failed: error %i\n", res);
        exit(1);
    }

    res = pthread_join(p->tid, &pret);
    if (res != 0)
    {
        printf("pthread_join() failed: error %i\n", res);
        exit(1);
    }
    free(arg);
    pthread_exit(NULL);
}

int main()
{
    int res;
    pthread_t tid;
    S *p1;

    printf("main indice 0\n");
    fflush(stdout);
    usleep(1000);
    p1 = malloc(sizeof(S));
    if (p1 == NULL)
    {
        perror("malloc failed");
        exit(1);
    }
    p1->indice = 1;
    p1->tid = pthread_self();
    res = pthread_create(&tid, NULL, func, (void *)p1);
    if (res)
    {
        printf("pthread_create() failed: error %i\n", res);
        exit(1);
    }

    printf("fine main\n");
    fflush(stdout);

    pthread_exit(NULL);
    return (0);
}
