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
#define NUMSOBRI 4
#define NUMUBRIACHI 2

#define UBRIACO 0
#define SOBRIO 1

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condFuniviaLibera = PTHREAD_COND_INITIALIZER;
pthread_cond_t condSalito = PTHREAD_COND_INITIALIZER;
pthread_cond_t condFineGiro = PTHREAD_COND_INITIALIZER;

int posti[2] = {-1, -1};
int numPasseggeri = 0;

void *Ubriaco(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Ubriaco %" PRIiPTR "", indice);

	while (1)
	{
		int indicePosto;
		DBGpthread_mutex_lock(&mutex, Label);

		while (numPasseggeri != 0)
			DBGpthread_cond_wait(&condFuniviaLibera, &mutex, Label);

		indicePosto = 0;
		numPasseggeri++;

		/* sale il sobrio */
		posti[0] = UBRIACO;

		printf("%s - Sale in posizione %d \n", Label, indicePosto);
		fflush(stdout);

		/* avvisa che è salito */
		DBGpthread_cond_signal(&condSalito, Label);

		/* aspetta che sia finito il giro */
		DBGpthread_cond_wait(&condFineGiro, &mutex, Label);

		/* gioia */
		printf("%s - VOMITA\n", Label);
		fflush(stdout);

		/* libero il posto */
		posti[0] = -1;
		numPasseggeri--;

		DBGpthread_cond_broadcast(&condFuniviaLibera, Label);

		DBGpthread_mutex_unlock(&mutex, Label);

	}
}

void *Sobrio(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Sobrio %" PRIiPTR "", indice);

	while (1)
	{
		int indicePosto;
		DBGpthread_mutex_lock(&mutex, Label);

		while (numPasseggeri == 2 || (numPasseggeri == 1 && posti[0] == UBRIACO))
			DBGpthread_cond_wait(&condFuniviaLibera, &mutex, Label);

		indicePosto = numPasseggeri;
		numPasseggeri++;

		/* sale il sobrio */
		posti[indicePosto] = SOBRIO;

		printf("%s - Sale in posizione %d\n", Label, indicePosto);
		fflush(stdout);

		/* avvisa che è salito */
		DBGpthread_cond_signal(&condSalito, Label);

		/* aspetta che sia finito il giro */
		DBGpthread_cond_wait(&condFineGiro, &mutex, Label);

		/* gioia */
		printf("%s - URRAAA\n", Label);
		fflush(stdout);

		/* libero il posto */
		posti[indicePosto] = -1;
		numPasseggeri--;

		/* se sono l'ultimo sceso avviso che è vuoto */
		if (numPasseggeri == 0)
		{
			DBGpthread_cond_broadcast(&condFuniviaLibera, Label);
		}

		DBGpthread_mutex_unlock(&mutex, Label);

	}
}

void *Funivia(void *arg)
{
	char Label[128];
	sprintf(Label, "Funivia");

	while (1)
	{
		DBGpthread_mutex_lock(&mutex, Label);

		/* Aspetto che salgano in due */
		while (numPasseggeri == 0 || (numPasseggeri == 1 && posti[0] != UBRIACO && posti[1] == -1))
			DBGpthread_cond_wait(&condSalito, &mutex, Label);

		DBGpthread_mutex_unlock(&mutex, Label);

		printf("%s - Inzia salita\n", Label);
		fflush(stdout);

		sleep(1);

		printf("%s - Arrivato in cima\n", Label);
		fflush(stdout);

		sleep(1);

		printf("%s - Fine giro\n", Label);
		
		DBGpthread_mutex_lock(&mutex, Label);

		/* avvisa fine giro	*/
		DBGpthread_cond_broadcast(&condFineGiro, Label);

		DBGpthread_mutex_unlock(&mutex, Label);
	}
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i;

	/* inizializzate le vostre variabili globali */

	rc = pthread_create(&th, NULL, Funivia, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_create failed");

	for (i = 0; i < NUMSOBRI; i++)
	{
		rc = pthread_create(&th, NULL, Sobrio, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	for (i = 0; i < NUMUBRIACHI; i++)
	{
		rc = pthread_create(&th, NULL, Ubriaco, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}
