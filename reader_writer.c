/* reader writer using semaphore */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


pthread_t r1,r2,r3,w1;
sem_t mutex,db;
int rc=0;

void *reader(void *j)
{
	int i;
	while(1)
	{
		sem_wait(&mutex);
		rc++;
		if(rc==1)
		sem_wait(&db);
		sem_post(&mutex);
		
		printf("READER-%s  !\n",((char *)j));
		sleep(1);
		sem_wait(&mutex);
		rc--;
		if(rc==0)
		sem_post(&db);
		sem_post(&mutex);
	}
}

void *writer()
{
	int i;
	while(1)
	{
		sem_wait(&db);
		
		printf("WRITER !\n");
		sem_post(&db);
		
	}

}

int main()
{
	printf("READER - WRITER !!!\n");
	sem_init(&mutex, 0, 1);
	sem_init(&db, 0, 1);
	
	
	pthread_create(&r1,NULL,reader,(void *)"1");
	pthread_create(&r2,NULL,reader,(void *)"2");
	pthread_create(&r3,NULL,reader,(void *)"3");
	pthread_create(&w1,NULL,writer,NULL);
	
	
	
	pthread_join(r1,NULL);
	
	pthread_join(r2,NULL);
	pthread_join(w1,NULL);
	pthread_join(r3,NULL);
	printf("Exit\n");
	return 0;
}