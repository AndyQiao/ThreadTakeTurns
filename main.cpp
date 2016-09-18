#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

const int NUM=100;
sem_t even,odd;
void* PrintEven(void* p)
{
	for(int i=0;i<=NUM;i+=2)
	{
		sem_wait(&even);
		cout<<i<<" ";
		sem_post(&odd);
	}
}
void* PrintOdd(void* p)
{
	for(int i=1;i<=NUM;i+=2)
	{
		sem_wait(&odd);
		cout<<i<<" ";
		sem_post(&even);
	}
}
int main()
{
	sem_init(&even,0,1);
	sem_init(&odd,0,0);
	
	pthread_t pid[2];
	pthread_create(&pid[0],NULL,PrintOdd,NULL);
	pthread_create(&pid[1],NULL,PrintEven,NULL);
	
	for(int i=0;i<2;++i)
	{
		pthread_join(pid[i],NULL);
	}
	cout<<endl;
	return 0;
}
