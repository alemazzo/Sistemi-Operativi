/* file:  vacche.c */

#ifndef _THREAD_SAFE
#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE /* per random e srandom */
#endif

/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h> /* exit() etc */
#include <stdlib.h> /* random  srandom */
#include <stdio.h>
#include <string.h> /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h>	  /* timespec{} for pselect() */
#include <limits.h>	  /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>	  /* uint64_t intptr_t */
#include <inttypes.h> /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMBANCHE 3
#define NUMTHREADDEPOSITI 5
#define NUMTHREADPRELIEVI 4

pthread_t banche[NUMBANCHE];
int totale[NUMBANCHE];
int operazioni[NUMBANCHE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Deposito(void *arg)
{

	intptr_t banca = (intptr_t)arg;
	printf("Thread Deposito banca %d -> started\n", (int)banca);
	fflush(stdout);
	while (1)
	{
		sleep(1);
		DBGpthread_mutex_lock(&mutex, "Deposito");
		totale[banca] += 10;
		operazioni[banca]++;
		usleep(100000);
		DBGpthread_mutex_unlock(&mutex, "Deposito");
	}
}

void *Prelievo(void *arg)
{
	intptr_t banca = (intptr_t)arg;
	printf("Thread Prelievo banca %d -> started\n", (int)banca);
	fflush(stdout);
	while (1)
	{
		sleep(1);
		DBGpthread_mutex_lock(&mutex, "Prelievo");
		totale[banca] -= 9;
		operazioni[banca]++;
		usleep(100000);
		DBGpthread_mutex_unlock(&mutex, "Prelievo");
	}
}

void *BancaDiItalia(void *arg)
{
	while (1)
	{
		int i, numOperazioni = 0, totaleFondi = 0;

		sleep(10);
		DBGpthread_mutex_lock(&mutex, "BancaDiItalia");
		for (i = 0; i < NUMBANCHE; i++)
		{
			printf("Banca %d :\n\tTotale => %d\n\tOperazioni => %d \n", i, totale[i], operazioni[i]);
			fflush(stdout);
			numOperazioni += operazioni[i];
			totaleFondi += totale[i];
		}
		printf("\nResoconto : \n\tTotale => %d\n\tOperazioni => %d\n", totaleFondi, numOperazioni);
		fflush(stdout);
		sleep(1);
		DBGpthread_mutex_unlock(&mutex, "BancaDiItalia");
	}
}

int main()
{

	pthread_t pid;
	intptr_t index;
	int rc, i;
	for (i = 0; i < NUMBANCHE; i++)
	{
		totale[i] = 0;
		operazioni[i] = 0;
	}
	printf("Variables initilized\n");
	fflush(stdout);

	for (index = 0; index < NUMBANCHE; index++)
	{
		for (i = 0; i < NUMTHREADDEPOSITI; i++)
		{
			rc = pthread_create(&pid, NULL, Deposito, (void *)index);
			if (rc)
				PrintERROR_andExit(rc, "pthread_create failed");
		}

		for (i = 0; i < NUMTHREADPRELIEVI; i++)
		{
			rc = pthread_create(&pid, NULL, Prelievo, (void *)index);
			if (rc)
				PrintERROR_andExit(rc, "pthread_create failed");
		}
	}

	rc = pthread_create(&pid, NULL, BancaDiItalia, NULL);
	if (rc)
		PrintERROR_andExit(rc, "pthread_create failed");

	pthread_exit(NULL);
}