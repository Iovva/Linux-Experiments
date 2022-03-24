#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_barrier_t barrier;
int miere = 0;
#define PN 10
#define UN 5
#define AN 5
#define F 50

void* urs(void* a){
	int nr = (int)a;

	pthread_mutex_lock(&mutex);
	printf("Urs %d asteapta\n", nr);
 	pthread_mutex_unlock(&mutex);
	pthread_barrier_wait(&barrier);	
	
	while(1) {
		pthread_mutex_lock(&mutex);
		if (miere >= F) {
			miere -= F;
			printf("Urs %d mananca\n", nr);
		}
		else{
			pthread_cond_broadcast(&cond);
			printf("Urs %d a fost pacalit de vulpe\n", nr);
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* alb(void* a){	
	int nr = (int)a;

 	pthread_mutex_lock(&mutex);
        printf("Alb %d asteapta\n", nr);
        pthread_mutex_unlock(&mutex);
        pthread_barrier_wait(&barrier);	
	
	while(1){
		pthread_mutex_lock(&mutex);
		miere++;
		printf("Alb %d adauga\n", nr);
		pthread_mutex_unlock(&mutex);
	}	
	return NULL;
}

void* pad(void* a){
	int nr = (int)a;

	pthread_mutex_lock(&mutex);
        printf("Padurarul %d asteapta\n", nr);
        pthread_mutex_unlock(&mutex);
        pthread_barrier_wait(&barrier);


	while(1){
		pthread_mutex_lock(&mutex);
		while(miere >= F)
			pthread_cond_wait(&cond, &mutex);
		miere += 10;
		printf("Padurarul %d salveaza situatia\n", nr);
		pthread_mutex_unlock(&mutex);		
	}
	return NULL;
}

int main(int argc, char** argv){

	pthread_t u_t[UN], a_t[AN], p_t[PN];
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);	 
	pthread_barrier_init(&barrier, NULL, UN + AN + PN);
	
	int i;	
	
	for(i = 0; i < PN; i++){
		pthread_create(&p_t[i], NULL, pad, (void*)i);
	}

        for(i = 0; i < AN; i++){
                pthread_create(&a_t[i], NULL, alb, (void*)i);
        }

	for(i = 0; i < UN; i++){
		pthread_create(&u_t[i], NULL, urs, (void*)i);
	}

 	for(i = 0; i < PN; i++)
              pthread_join(p_t[i], NULL);

	for(i = 0; i < AN; i++)
		pthread_join(a_t[i], NULL);
	
	for(i = 0; i < UN; i++)
		pthread_join(u_t[i], NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);		
	pthread_barrier_destroy(&barrier);

	return 0;
}
