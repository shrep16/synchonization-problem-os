#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 

  
#define N 5 
#define THINKING 0 
#define HUNGRY 1 
#define EATING 2 
#define LEFT (i + N-1) % N 
#define RIGHT (i + 1) % N 
  
int state[N]; 
int pNo[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex,S[N]; 
 
  
void test(int i) 
{ 
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) 
	{ 
        state[i] = EATING;
        
  
        printf("%d philosopher takes fork %d and %d\n", i + 1, LEFT + 1, RIGHT + 1); 
         
        sem_post(&S[i]); 
	sleep(1); 
    } 
} 
  
 
void take_fork(int i) 
{ 
  
    sem_wait(&mutex); 
    state[i] = HUNGRY; 
    printf("%d philosopher is Hungry\n", i + 1); 
  
    
    test(i); 
  
    sem_post(&mutex); 
    sleep(1);
    sem_wait(&S[i]); 
  
     
} 
  
 
void put_fork(int i) 
{ 
  
    sem_wait(&mutex);
    state[i] = THINKING; 
    
    printf("%d philosopher putting fork %d and %d down\n", i + 1, LEFT + 1, RIGHT+ 1); 
    printf("%d philosopher is thinking after putting down the forks\n", i + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex);
    sleep(1); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num;
 	printf("%d philosopher is thinking \n",(*i)+1);
        take_fork(*i);
	printf("%d philosopher is eating \n",(*i)+1); 
        put_fork(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
    sem_init(&mutex, 0, 1); 
    

    for (i = 0; i < N; i++) 
        sem_init(&S[i], 0, 0); 

  
    for (i = 0; i < N; i++) 
	{ 
  		pthread_create(&thread_id[i], NULL, philospher, &pNo[i]); 
  		
        	
    	} 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL);

    return 0; 
} 
