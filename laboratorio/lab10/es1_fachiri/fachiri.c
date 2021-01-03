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

#define NUMFACHIRI 2
#define NUMSPADE 10

pthread_t fachiri[NUMFACHIRI];
pthread_mutex_t mutex[NUMSPADE];

void *Fachiro(void *arg)
{
	int i;
	intptr_t index = (intptr_t)arg;

	for (i = 0; i < NUMSPADE; i++)
	{
		DBGpthread_mutex_lock(&mutex[i], "Fachiro");
		sleep(1);
		printf("fachiro %d si trafigge con spada %d -> AAAAAAAAA\n", (int)index, i);
		fflush(stdout);
	}

	for (i = 0; i < NUMSPADE; i++)
	{
		DBGpthread_mutex_unlock(&mutex[i], "Fachiro");
	}

	pthread_exit(NULL);
}

int main()
{

	pthread_t pid;
	intptr_t index;
	int rc, i;
	for (i = 0; i < NUMSPADE; i++)
	{
		pthread_mutex_init(&mutex[i], NULL);
	}

	for (i = 0; i < NUMFACHIRI; i++)
	{
		index = i;
		rc = pthread_create(&pid, NULL, Fachiro, (void *)index);
		if (rc)
			PrintERROR_andExit(rc, "pthread_create failed");
	}

	pthread_exit(NULL);
}