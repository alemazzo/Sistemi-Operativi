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
#define NUMPERSONE 5

int numPersoneAlTavolo = 0;
int pizzaAlTavolo = 0;

pthread_mutex_t mutexTavolo = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexPizzaiolo = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condInizioMangiare = PTHREAD_COND_INITIALIZER;
pthread_cond_t condTavoloLibero = PTHREAD_COND_INITIALIZER;
pthread_cond_t condPizzaioloPortaciLaPizza = PTHREAD_COND_INITIALIZER;
pthread_cond_t condPizzaProntaNelTavolo = PTHREAD_COND_INITIALIZER;

void *Pizzaiolo(void *arg)
{
	char Label[128];
	sprintf(Label, "Pizzaiolo");

	DBGpthread_mutex_lock(&mutexPizzaiolo, Label);
	while (1)
	{

		printf("%s - Aspetta di venire chiamato...\n", Label);
		fflush(stdout);

		DBGpthread_cond_wait(&condPizzaioloPortaciLaPizza, &mutexPizzaiolo, Label);

		DBGpthread_mutex_lock(&mutexTavolo, Label);

		pizzaAlTavolo = 1;
		if (numPersoneAlTavolo == 4)
			DBGpthread_cond_broadcast(&condInizioMangiare, Label);

		DBGpthread_mutex_unlock(&mutexTavolo, Label);
		/* porta la pizza */

		printf("%s - Ha portato la pizza al tavolo e se ne va\n", Label);
		fflush(stdout);
	}
}

void *Persona(void *arg)
{
	char Label[128];
	intptr_t indice;
	indice = (intptr_t)arg;
	sprintf(Label, "Persona %" PRIiPTR "", indice);

	while (1)
	{
		DBGpthread_mutex_lock(&mutexTavolo, Label);

		/* aspetto che si svuoti il tavolo per tentare di sedermi */
		while (numPersoneAlTavolo >= 4)
			DBGpthread_cond_wait(&condTavoloLibero, &mutexTavolo, Label);

		printf("%s - Si siede al tavolo\n", Label);
		fflush(stdout);
		numPersoneAlTavolo++;

		/* se sono il terzo avviso il pizzaiolo */
		if (numPersoneAlTavolo == 3)
		{
			DBGpthread_cond_signal(&condPizzaioloPortaciLaPizza, Label);
			printf("%s - Avvisa il pizzaiolo\n", Label);
			fflush(stdout);
		}

		if (numPersoneAlTavolo == 4 && pizzaAlTavolo == 1)
		{
			printf("%s - Avvisa che si inizia a mangiare\n", Label);
			fflush(stdout);
			DBGpthread_cond_broadcast(&condInizioMangiare, Label);
		}
		else
		{
			if (numPersoneAlTavolo < 4)
			{
				printf("%s - Aspetto che il tavolo sia pieno\n", Label);
				fflush(stdout);
				/* aspetto che mi dicano che posso mangiare */
				DBGpthread_cond_wait(&condInizioMangiare, &mutexTavolo, Label);
			}
			else if (pizzaAlTavolo == 0)
			{
				printf("%s - Aspetta che arrivi la pizza\n", Label);
				fflush(stdout);
				/* aspetto che mi dicano che posso mangiare */
				DBGpthread_cond_wait(&condInizioMangiare, &mutexTavolo, Label);
			}
		}

		printf("%s - Inizia a mangiare\n", Label);
		fflush(stdout);
		DBGpthread_mutex_unlock(&mutexTavolo, Label);

		sleep(3);

		DBGpthread_mutex_lock(&mutexTavolo, Label);

		printf("%s - Ha finito di mangiare\n", Label);
		fflush(stdout);

		numPersoneAlTavolo--;
		if (numPersoneAlTavolo == 0)
		{
			pizzaAlTavolo = 0;
			DBGpthread_cond_broadcast(&condTavoloLibero, Label);
		}
		

		DBGpthread_mutex_unlock(&mutexTavolo, Label);

		sleep(2 + indice);
	}
}

int main(int argc, char *argv[])
{
	pthread_t th;
	int rc;
	intptr_t i;

	/* inizializzate le vostre variabili globali */

	rc = pthread_create(&th, NULL, Pizzaiolo, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_create failed");

	for (i = 0; i < NUMPERSONE; i++)
	{
		rc = pthread_create(&th, NULL, Persona, (void *)i);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}
