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
#define NUMALIENI 5

pthread_t th;

intptr_t postiCasa[2] = {-1, -1};
intptr_t primoInCasa = -1;
int numAlieniInCasa = 0;
int numAlieniFuoriCasa = NUMALIENI;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condAlienoEsceDiCasa = PTHREAD_COND_INITIALIZER;
pthread_cond_t condAlienoEntraInCasa = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutexDispenserAlieni = PTHREAD_MUTEX_INITIALIZER;
intptr_t numAlieni = 1;

void *Alieno(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Alieno %" PRIiPTR "", indice);

	DBGpthread_mutex_lock(&mutex, Label);

	while (numAlieniInCasa == 2)
		DBGpthread_cond_wait(&condAlienoEsceDiCasa, &mutex, Label);

	numAlieniFuoriCasa--;
	numAlieniInCasa++;
	
	if (postiCasa[0] == -1)
	{
		postiCasa[0] = indice;
		printf("%s - Entra in posizione 0...\n", Label);
		fflush(stdout);
	}
	else
	{
		postiCasa[1] = indice;
		printf("%s - Entra in posizione 1...\n", Label);
		fflush(stdout);
	}

	DBGpthread_cond_signal(&condAlienoEntraInCasa, Label);

	/* è entrato in casa, ora cerca di scappare */
	
	if (postiCasa[0] != indice)
		DBGpthread_cond_wait(&condAlienoEsceDiCasa, &mutex, Label);

	
	/* se è il primo e non c'è nessun altro allora devo aspettare che ne entri un altro */
	if (postiCasa[1] == -1)
	{
		DBGpthread_cond_wait(&condAlienoEntraInCasa, &mutex, Label);
	}

	/* una volta che ne è entrato un altro può uscire */
	/* assegno il nuovo primo ad uscire */
	postiCasa[0] = postiCasa[1];
	postiCasa[1] = -1;
	numAlieniInCasa--;
	printf("%s - Era il primo ed esce...\n", Label);
	fflush(stdout);

	/* avviso che sono uscito cosi può entrare un altro */
	DBGpthread_cond_broadcast(&condAlienoEsceDiCasa, Label);


	if (numAlieniFuoriCasa < 3)
	{
		int rc;
	
		printf("%s - Vede che ci sono pochi alieni, quindi ne crea 2...\n", Label);
		fflush(stdout);
	
		DBGpthread_mutex_lock(&mutexDispenserAlieni, Label);

		rc = pthread_create(&th, NULL, Alieno, (void *)numAlieni++);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");

		rc = pthread_create(&th, NULL, Alieno, (void *)numAlieni++);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");

			numAlieniFuoriCasa+=2;
			
		DBGpthread_mutex_unlock(&mutexDispenserAlieni, Label);
	}
	DBGpthread_mutex_unlock(&mutex, Label);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	int rc;
	intptr_t i;

	/* inizializzate le vostre variabili globali */

	for (i = 0; i < NUMALIENI; i++)
	{
		rc = pthread_create(&th, NULL, Alieno, (void *)numAlieni++);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}
