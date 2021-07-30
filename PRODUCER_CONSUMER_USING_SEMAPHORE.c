#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define buffer_size 10
//#define THREAD_NUM 2

pthread_mutex_t mutex;
sem_t full,empty;
int buffer[buffer_size];
int counter;
//pthread_t tid[THREAD_NUM];
pthread_t t;

void initialize()
{
	pthread_mutex_init(&mutex,NULL);
	sem_init(&full,1,0);
	sem_init(&empty,1,buffer_size);
	counter=0;
}
void insert_item(int item)
{
	buffer[counter++]=item;
}
int remove_item()
{
	return (buffer[--counter]);
}
void *producer(void *arg)
{
	int item,wait_time;
	wait_time=rand()%5;
	sleep(wait_time);
	item=rand()%15;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	printf("\nproducer produced %d",item);
	insert_item(item);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
}
void *consumer(void *arg)
{
	int item=0,wait_time;
	wait_time=rand()%3;
	sleep(wait_time);
	//item=rand()%15;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	item=remove_item();
	printf("\nconsumer consumed %d",item);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}

int main()
{
	int i,n1,n2;
	srand(time(NULL));
	printf("\n Enter no of producer:");
	scanf("%d",&n1);
	printf("\n Enter no of consumer:");
	scanf("%d",&n2);
	initialize();
	for(i=0;i<n1;i++)
	{
		pthread_create(&t,NULL,&producer,NULL);
	}
	for(i=0;i<n2;i++)
	{
		pthread_create(&t,NULL,&consumer,NULL);
		sleep(5);
	}
	return 0;
}





