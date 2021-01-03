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
#define NUMATTACCHINI 2
#define NUMVECCHIETTI 4

int numeroAttacchini = 0;
int numeroVecchietti = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condAttachinoArriva = PTHREAD_COND_INITIALIZER;
pthread_cond_t condAttacchiniSeNeVanno = PTHREAD_COND_INITIALIZER;
pthread_cond_t condVecchiettiSeNeVanno = PTHREAD_COND_INITIALIZER;

void *Attachino(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Attachino %" PRIiPTR "", indice);

	while (1)
	{
		DBGpthread_mutex_lock(&mutex, Label);

		while (numeroVecchietti > 0){
			printf("%s - Aspetta che se ne vadano i vecchietti\n", Label);
			fflush(stdout);
			DBGpthread_cond_wait(&condVecchiettiSeNeVanno, &mutex, Label);
		}
			

		numeroAttacchini++;
		if (numeroAttacchini == 1)
		{
			printf("%s - Aspetta l'altro\n", Label);
			fflush(stdout);
			DBGpthread_cond_wait(&condAttachinoArriva, &mutex, Label);
		}
		else
			DBGpthread_cond_signal(&condAttachinoArriva, Label);

		DBGpthread_mutex_unlock(&mutex, Label);

		printf("%s - Inizia a lavorare\n", Label);
		fflush(stdout);

		sleep(2);

		printf("%s - Finisce di lavorare\n", Label);
		fflush(stdout);

		DBGpthread_mutex_lock(&mutex, Label);

		numeroAttacchini--;
		if(numeroAttacchini == 0) DBGpthread_cond_broadcast(&condAttacchiniSeNeVanno, Label);

		DBGpthread_mutex_unlock(&mutex, Label);

		printf("%s - Va a fare un giro\n", Label);
		fflush(stdout);
		sleep(2);
		printf("%s - Tornato\n", Label);
		fflush(stdout);
	}
}

void *Vecchietto(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Vecchietto %" PRIiPTR "", indice);

	while (1)
	{
		DBGpthread_mutex_lock(&mutex, Label);
		
		DBGpthread_cond_wait(&condAttacchiniSeNeVanno, &mutex, Label);
		numeroVecchietti++;
		DBGpthread_mutex_unlock(&mutex, Label);

		printf("%s - Inizia a guardare\n", Label);
		fflush(stdout);

		sleep(3);

		printf("%s - Se ne va\n", Label);
		fflush(stdout);

		DBGpthread_mutex_lock(&mutex, Label);
		numeroVecchietti--;
		if (numeroVecchietti == 0)
		{
			DBGpthread_cond_broadcast(&condVecchiettiSeNeVanno, Label);
		}

		DBGpthread_mutex_unlock(&mutex, Label);
		sleep(1 + (indice));
	}
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i;

	/* inizializzate le vostre variabili globali */

	for (i = 0; i < NUMVECCHIETTI; i++)
	{
		rc = pthread_create(&th, NULL, Vecchietto, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	for (i = 0; i < NUMATTACCHINI; i++)
	{
		rc = pthread_create(&th, NULL, Attachino, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}
