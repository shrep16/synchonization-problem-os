/* producer consumer using mutex */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>




pthread_t p,c;
pthread_mutex_t s;
sem_t full,empty;
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
		pthread_mutex_lock(&s);
		add();
		
		pthread_mutex_unlock(&s);
		sleep(1);
		sem_post(&full);
		sleep(1);
	}
}

void *consumer()
{
	int i=0;
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&s);
		delete();
		
		pthread_mutex_unlock(&s);
		sleep(1);
		sem_post(&empty);
		sleep(1);
	}
}

int main()
{
	printf("PRODUCER-CONSUMER!!!\n");
	pthread_mutex_init(&s, NULL);
	sem_init(&empty,0,10);
	sem_init(&full, 0,0);
	
	pthread_create(&p,NULL,producer,NULL);
	pthread_create(&c,NULL,consumer,NULL);	
	
	
	pthread_join(c,NULL);
	pthread_join(p,NULL);
	printf("Exit\n");
	return 0;
}
