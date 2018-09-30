/* producer consumer using semaphore */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>




pthread_t p,c;

sem_t s,full,empty;
int arr[30]={0};
int in=0;


void add()
{
	
	int item;
	
	
	item=rand()%100;
	arr[in++]=item;
	printf("Producer :%d added to the queue\n",item);
}

void delete()
{	
	int item;
	
	item=arr[--in];
	
	printf("Consumer :%d consumed from the queue\n",item);
	
}

void *producer()
{
	int i=0;
	while(1)
	{
		sem_wait(&empty);
		sem_wait(&s);
		add();
		sleep(1);
		sem_post(&s);
		sem_post(&full);
	}
}

void *consumer()
{
	int i=0;
	while(1)
	{
		sem_wait(&full);
		sem_wait(&s);
		delete();
		sleep(1);
		sem_post(&s);
		sem_post(&empty);
	}
}

int main()
{
	printf("PRODUCER-CONSUMER!!!\n");
	sem_init(&s,0,1);
	sem_init(&empty,0,10);
	sem_init(&full, 0,0);
	
	pthread_create(&p,NULL,producer,NULL);
	pthread_create(&c,NULL,consumer,NULL);	
	
	
	pthread_join(c,NULL);
	pthread_join(p,NULL);
	printf("Exit\n");
	return 0;
}