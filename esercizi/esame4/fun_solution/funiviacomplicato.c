/* funiviacomplicato.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/mman.h>  /* shm_* stuff, and mmap() */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /* timeval{} for select() */
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <sys/wait.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h> 

#include "DBGpthread.h"


#define NUMSOBRI 4
#define NUMUBRIACHI 2 


typedef struct sharedBuffer {
	/* dati da proteggere */
	int numSobriSu;
	int numUbriachiSu;
	int salite;				/* passeggeri all'inizio possono salire su funivia */
	int sedili[2]; /* solo per debug */

	/* variabili per la sincronizzazione */
	pthread_mutex_t  mutex; 
	pthread_cond_t   condPasseggeriScesi, condPasseggeriSalite, 
									 condFuniviaParti, condFineGiro; 
	int funiviaFaiWait;
} SharedBuffer;
SharedBuffer *P;


void Ubriaco (int indice) 
{ 
	char Ulabel[128];

	sprintf(Ulabel,"U%d",indice);

	while(1) {
		DBGpthread_mutex_lock(&P->mutex,Ulabel); 

		/*se è già presente un ubriaco o almeno un sobrio attendo il prossimo giro*/
		while( P->salite==0 || P->numSobriSu > 0 || P->numUbriachiSu > 0 ){

			printf("Ubriaco %s attende prossimo giro\n", Ulabel);
			fflush(stdout);

			DBGpthread_cond_wait(&P->condPasseggeriSalite,&P->mutex,Ulabel);
		}

		printf("Ubriaco %s sale sulla funivia\n",Ulabel);
		fflush(stdout);

		/*incremento numero di ubriachi a bordo*/
		P->numUbriachiSu++;

		/* solo per debug */
		P->sedili[0]=indice;
		P->sedili[1]=-1;

		/* non puo' salire piu' nessuno */
		P->salite=0;
		/*comunico alla funivia che può partire*/
		P->funiviaFaiWait = 0;
		DBGpthread_cond_signal(&P->condFuniviaParti, Ulabel);
		/*attendo la fine del giro*/
		DBGpthread_cond_wait(&P->condFineGiro,&P->mutex,Ulabel);

		P->numUbriachiSu--;
		printf("Ubriaco %s scende dalla funivia, evviva\n", Ulabel);
		fflush(stdout);

		DBGpthread_cond_signal(&P->condPasseggeriScesi, Ulabel);
		
		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&P->mutex,Ulabel); 
	}
	pthread_exit(NULL); 
} 

void Sobrio (int indice) 
{ 
	char Slabel[128];

	sprintf(Slabel,"S%d",indice);
	
	while(1) {
		DBGpthread_mutex_lock(&P->mutex,Slabel); 
		/*se è già presente un ubriaco o almeno due sobri attendo il prossimo giro*/
		while( P->salite==0 || P->numSobriSu >=2 || P->numUbriachiSu > 0) {

			printf("Sobrio %s attende prossimo giro\n",Slabel);
			fflush(stdout);

			DBGpthread_cond_wait(&P->condPasseggeriSalite,&P->mutex,Slabel);
		}

		printf("Sobrio %s sale sulla funivia\n", Slabel);
		fflush(stdout);

		/* solo per debug */
		if(P->numSobriSu==0)
			P->sedili[0]=indice;
		else
			P->sedili[1]=indice;

		/*incremento numero di sobri a bordo*/
		P->numSobriSu++;
		if(P->numSobriSu==2){
			/* non puo' salire piu' nessuno */
			P->salite=0;
			/*comunico alla funivia che può partire*/
			P->funiviaFaiWait = 0;
			DBGpthread_cond_signal(&P->condFuniviaParti, Slabel);
		}
		/*attendo la fine del giro*/
		DBGpthread_cond_wait(&P->condFineGiro,&P->mutex,Slabel);

		
		P->numSobriSu--;
		printf("Sobrio %s scende dalla funivia, evviva\n", Slabel);
		fflush(stdout);

		if(P->numSobriSu==0)
			DBGpthread_cond_signal(&P->condPasseggeriScesi, Slabel);

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&P->mutex,Slabel); 
	}
	pthread_exit(NULL); 
} 


void stampo_composizione_passeggeri( char *Flabel) {

	if( P->numUbriachiSu!=1 && P->numSobriSu!=2 ) {
		printf("Funivia %s porta carico NON AMMESSO. %d sobri e %d ubriachi\n STOP\n",
			Flabel, P->numSobriSu, P->numUbriachiSu);
		fflush(stdout);
		exit(1);
	}
	else {
		if( P->numUbriachiSu==1 ) {
			printf("Funivia %s trasporta %d sobri e %d ubriachi (%d)\n",
				Flabel, P->numSobriSu, P->numUbriachiSu, P->sedili[0]);
			fflush(stdout);
		}
		else if( P->numSobriSu==2 ) {
			printf("Funivia %s trasporta %d sobri (%d %d) e %d ubriachi\n",
				Flabel, P->numSobriSu, P->sedili[0], P->sedili[1], P->numUbriachiSu );
			fflush(stdout);
		}
	}
}


void *Funivia (int indice) 
{ 
	
	char Flabel[128];
	
	sprintf(Flabel,"F%d",indice);
	
	while(1) {
		DBGpthread_mutex_lock(&P->mutex,Flabel); 
		/*se la funivia non è piena attendo che lo diventi*/
		if( P->funiviaFaiWait) {

			printf("Funivia %s attende passeggeri\n", Flabel);
			fflush(stdout);

			DBGpthread_cond_wait(&P->condFuniviaParti,&P->mutex,Flabel);
		}
		
		stampo_composizione_passeggeri(Flabel);
		
		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&P->mutex, Flabel); 


		/*funivia sale*/
		DBGsleep(1, Flabel);
		printf("Funivia %s arrivata in cima\n", Flabel);fflush(stdout);
		/*funivia scende*/
		DBGsleep(1, Flabel);
		printf("Funivia %s ridiscesa \n", Flabel);fflush(stdout);

		
		DBGpthread_mutex_lock(&P->mutex,Flabel); 
		
		/*comunico che il giro è finito*/
		DBGpthread_cond_broadcast(&P->condFineGiro, Flabel);
		/*i passeggeri scendono*/

		/* aspetto che i passeggeri siano scesi tutti */
		DBGpthread_cond_wait(&P->condPasseggeriScesi,&P->mutex,Flabel);

		/* consento ai passeggeri in attesa di salire */
		P->salite=1;
		/*comunico ai passeggeri in attesa che possono salire*/
		DBGpthread_cond_broadcast(&P->condPasseggeriSalite, Flabel);
		/*nessun passeggero a bordo...*/
		P->funiviaFaiWait=1;

		/* rilascio mutua esclusione */
		DBGpthread_mutex_unlock(&P->mutex,Flabel); 

	}
	pthread_exit(NULL); 
}

int main (int argc, char* argv[] ) 
{ 
	int shmfd, rc, i;
	pid_t pid;
	int shared_seg_size = sizeof(SharedBuffer);
	pthread_mutexattr_t mattr;
	pthread_condattr_t cvattr;

	shmfd = shm_open( "/pedala", O_CREAT /*| O_EXCL*/ | O_RDWR, S_IRWXU );
	if (shmfd < 0) {
		perror("In shm_open()");
		exit(1);
	}
	/* adjusting mapped file size (make room for the whole segment to map) */
	rc = ftruncate(shmfd, shared_seg_size);
	if (rc != 0) {
		perror("ftruncate() failed");
		exit(1);
	}

	P = (SharedBuffer*)mmap(NULL, shared_seg_size,
		PROT_READ|PROT_WRITE, MAP_SHARED, shmfd, 0);
	if( P==MAP_FAILED )
	 		PrintERROR_andExit(errno,"mmap  failed");

	rc=pthread_mutexattr_init(&mattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutexattr_init  failed");
	rc=pthread_mutexattr_setpshared(&mattr,PTHREAD_PROCESS_SHARED);
	if( rc ) PrintERROR_andExit(rc,"pthread_mutexattr_setpshared  failed");
	rc=pthread_condattr_init(&cvattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_condattr_init  failed");
	rc=pthread_condattr_setpshared(&cvattr,PTHREAD_PROCESS_SHARED);
	if( rc ) PrintERROR_andExit(rc,"pthread_condattr_setpshared  failed");

	
	/*inizializzo strutture e  variabili per sincronizzazione*/
	rc = pthread_cond_init(&P->condPasseggeriSalite, &cvattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&P->condPasseggeriScesi, &cvattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&P->condFuniviaParti, &cvattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&P->condFineGiro, &cvattr);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_mutex_init(&P->mutex, &mattr ); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	
	/*inizializzo variabili globali da proteggere*/
	P->funiviaFaiWait=1;	/* la funivia aspetta che i passeggeri salgano */
	P->numSobriSu=0;			/* nessun sobrio e' salito */
	P->numUbriachiSu=0;	/* nessun ubriaco e' salito */
	P->salite=1;	/* la funivia e' a terra, consento ai passeggeri di salire */


	for(i=0;i<NUMSOBRI+NUMUBRIACHI;i++) {
		pid=fork();
		if(pid<0) 
			PrintERROR_andExit(errno,"fork failed");
		else if(pid==0) {
			if( i<NUMSOBRI )
				Sobrio(i);
			else 
				Ubriaco(i-NUMSOBRI);
			exit(0);
		}
	}
	Funivia(0); 

	return(0); 
} 
  
