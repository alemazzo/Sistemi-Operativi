/* file:  staffetta.c */

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


/* variabili globali da proteggere */

/* aggiungete le vostre variabili globali */

/* ruoli */
#define NUMATLETIALFA 5
#define NUMATLETIBETA 4

#define ALFA 1
#define BETA 0

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condAtleta = PTHREAD_COND_INITIALIZER;

int atleta = ALFA;
int indiceAtletaAlfa = 0;
int indiceAtletaBeta = 0;


void *AtletaAlfa(void *arg)
{
	char Label[128];
	intptr_t indice;
    indice = (intptr_t)arg;
	sprintf(Label, "Atleta Alfa %" PRIiPTR "", indice);

    while(1){

        DBGpthread_mutex_lock(&mutex, Label);
        while(!(atleta == ALFA && indiceAtletaAlfa == indice)) DBGpthread_cond_wait(&condAtleta, &mutex, Label);

        printf("%s - Inizia Giro\n", Label);
		fflush(stdout);
        sleep(1);
        printf("%s - Finisce Giro\n", Label);
		fflush(stdout);

        indiceAtletaAlfa = ( indiceAtletaAlfa + 1 ) % NUMATLETIALFA;
		atleta = BETA;
        DBGpthread_cond_broadcast(&condAtleta, Label);
        DBGpthread_mutex_unlock(&mutex, Label);
    }
}

void *AtletaBeta(void *arg)
{
	char Label[128];
	intptr_t indice;
    indice = (intptr_t)arg;
	sprintf(Label, "Atleta Beta %" PRIiPTR "", indice);

    while(1){

        DBGpthread_mutex_lock(&mutex, Label);
        while(!(atleta == BETA && indiceAtletaBeta == indice)) DBGpthread_cond_wait(&condAtleta, &mutex, Label);
		DBGpthread_mutex_unlock(&mutex, Label);

        printf("%s - Inizia Giro\n", Label);
		fflush(stdout);
        sleep(1);
        printf("%s - Finisce Giro\n", Label);
		fflush(stdout);
        
		DBGpthread_mutex_lock(&mutex, Label);
        indiceAtletaBeta = ( indiceAtletaBeta + 1 ) % NUMATLETIBETA;
		atleta = ALFA;
        DBGpthread_cond_broadcast(&condAtleta, Label);
        DBGpthread_mutex_unlock(&mutex, Label);
    }
}


int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i;

	/* inizializzate le vostre variabili globali */

	for (i = 0; i < NUMATLETIALFA; i++)
	{
		rc = pthread_create(&th, NULL, AtletaAlfa, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	for (i = 0; i < NUMATLETIBETA; i++)
	{
		rc = pthread_create(&th, NULL, AtletaBeta, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}
