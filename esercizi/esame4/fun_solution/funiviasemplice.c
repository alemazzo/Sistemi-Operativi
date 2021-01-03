/* funiviasemplice.c */

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
#include <pthread.h> 

#include "DBGpthread.h"



#define NUMSOBRI 4


/* dati da proteggere */
int numSobriSu=0;
int salite=1;				/* passeggeri all'inizio possono salire su funivia */
int sedili[2]; /* solo per debug */

/* variabili per la sincronizzazione */
pthread_mutex_t  mutex; 
pthread_cond_t   condPasseggeriScesi, condPasseggeriSalite, 
								 condFuniviaParti, condFineGiro; 
int funiviaFaiWait=1;


void *Sobrio (void *arg) 
{ 
	char Slabel[128];
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Slabel,"S%d",indice);
	
	while(1) {
		DBGpthread_mutex_lock(&mutex,Slabel); 
		/*se è già presente un ubriaco o almeno due sobri attendo il prossimo giro*/
		while( salite==0 || numSobriSu >=2 ) {

			printf("Sobrio %s attende prossimo giro\n",Slabel);
			fflush(stdout);

			DBGpthread_cond_wait(&condPasseggeriSalite,&mutex,Slabel);
		}

		printf("Sobrio %s sale sulla funivia\n", Slabel);
		fflush(stdout);

		/* solo per debug */
		if(numSobriSu==0)
			sedili[0]=indice;
		else
			sedili[1]=indice;

		/*incremento numero di sobri a bordo*/
		numSobriSu++;
		if(numSobriSu==2){
			/* non puo' salire piu' nessuno */
			salite=0;
			/*comunico alla funivia che può partire*/
			funiviaFaiWait = 0;
			DBGpthread_cond_signal(&condFuniviaParti, Slabel);
		}
		/*attendo la fine del giro*/
		DBGpthread_cond_wait(&condFineGiro,&mutex,Slabel);

		
		numSobriSu--;
		printf("Sobrio %s scende dalla funivia, evviva\n", Slabel);
		fflush(stdout);

		if(numSobriSu==0)
			DBGpthread_cond_signal(&condPasseggeriScesi, Slabel);

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex,Slabel); 
	}
	pthread_exit(NULL); 
} 


void stampo_composizione_passeggeri( char *Flabel) {

	if( numSobriSu!=2 ) {
		printf("Funivia %s porta carico NON AMMESSO. %d sobri STOP\n",
			Flabel, numSobriSu);
		fflush(stdout);
		exit(1);
	}
	else {
		printf("Funivia %s trasporta %d sobri (%d %d) \n",
			Flabel, numSobriSu, sedili[0], sedili[1] );
		fflush(stdout);
	}
}


void *Funivia (void *arg) 
{ 
	
	char Flabel[128];
	
	int indice;

	indice=*((int*)arg);
	free(arg);
	sprintf(Flabel,"F%d",indice);
	
	while(1) {
		DBGpthread_mutex_lock(&mutex,Flabel); 
		/*se la funivia non è piena attendo che lo diventi*/
		if( funiviaFaiWait) {

			printf("Funivia %s attende passeggeri\n", Flabel);
			fflush(stdout);

			DBGpthread_cond_wait(&condFuniviaParti,&mutex,Flabel);
		}
		
		stampo_composizione_passeggeri(Flabel);
		
		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex, Flabel); 


		/*funivia sale*/
		DBGsleep(1, Flabel);
		printf("Funivia %s arrivata in cima\n", Flabel);fflush(stdout);
		/*funivia scende*/
		DBGsleep(1, Flabel);
		printf("Funivia %s ridiscesa \n", Flabel);fflush(stdout);

		
		DBGpthread_mutex_lock(&mutex,Flabel); 
		
		/*comunico che il giro è finito*/
		DBGpthread_cond_broadcast(&condFineGiro, Flabel);
		/*i passeggeri scendono*/

		/* aspetto che i passeggeri siano scesi tutti */
		DBGpthread_cond_wait(&condPasseggeriScesi,&mutex,Flabel);

		/* consento ai passeggeri in attesa di salire */
		salite=1;
		/*comunico ai passeggeri in attesa che possono salire*/
		DBGpthread_cond_broadcast(&condPasseggeriSalite, Flabel);
		/*nessun passeggero a bordo...*/
		funiviaFaiWait=1;

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&mutex,Flabel); 

	}
	pthread_exit(NULL); 
}

int main (int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc, i, *intptr;
	
	/*inizializzo strutture e  variabili per sincronizzazione*/
	rc = pthread_cond_init(&condPasseggeriSalite, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&condPasseggeriScesi, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&condFuniviaParti, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&condFineGiro, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	funiviaFaiWait=1;
	/*inizializzo variabili globali da proteggere*/
	numSobriSu=0;
	salite=1;	/* la funivia e' a terra, consento ai passeggeri di salire */

	/*creo passeggeri sobri*/
	for(i=0;i<NUMSOBRI;i++) {
		intptr=malloc(sizeof(int));
		if( !intptr ) { printf("malloc failed\n");exit(1); }
		*intptr=i;
		rc=pthread_create( &th,NULL,Sobrio,(void*)intptr); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}
	
	/*creo funivia*/
	intptr=malloc(sizeof(int));
	if( !intptr ) { printf("malloc failed\n");exit(1); }
	*intptr=0;
	rc=pthread_create( &th,NULL,Funivia,(void*)intptr); 
	if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	
	
	pthread_exit(NULL); 

	return(0); 
} 
 
 
