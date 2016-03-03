/*
Using mutex, this program solves the problem of the program with race condition.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int ind = 0;
int arr[50];
pthread_mutex_t mutexvar;
pthread_cond_t condvar;

void *myFuncA(void *data)
{
	char t = *((char *)data);
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		pthread_mutex_lock(&mutexvar);
		if(ind >= sizeof(arr)/sizeof(int))
		{
			printf("\n No storage: Array full \n");
			pthread_cond_signal(&condvar);
			pthread_mutex_unlock(&mutexvar);
			break;
		}
		if(i == 35)
		{
			printf("Going to sleep.... \n");
			sleep(1);
			printf("Woke up! \n");
		}
		arr[ind] = i;
		printf("ThreadA %c: - The index value is: %d and the array value is: %d\n", t, ind, arr[ind]);
		ind++;
		pthread_cond_signal(&condvar);
		pthread_mutex_unlock(&mutexvar);
	}
	pthread_exit(NULL);
}

void *myFuncB(void *data)
{
	char t = *((char *)data);
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(int); i++)
	{		
		pthread_mutex_lock(&mutexvar);
		while(ind < 0 || ind > 50)
			pthread_cond_wait(&condvar, &mutexvar);
		if(i == 1 || i == 25 || i == 40)
		{
			printf("Going to sleep.... \n");
			sleep(1);
			printf("Woke up! \n");
		}
		ind--;
		printf("ThreadB %c: - The index value is: %d and the array value is: %d\n", t, ind, arr[ind]);
		arr[ind] = -1;
		if(ind < 0)
		{
			printf("\n Nothing stored: Array empty \n");
			pthread_mutex_unlock(&mutexvar);
			break;
		}
		pthread_mutex_unlock(&mutexvar);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t thread[2];
	int thread_id;
	int status;
	pthread_mutex_init(&mutexvar, NULL);
	pthread_cond_init(&condvar, NULL);
	char a = '1', b = '2';
	thread_id = pthread_create(&thread[1], NULL, (void *)myFuncB, (void *)&b);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[0], NULL, (void *)myFuncA, (void *)&a);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	printf("Hello! Just before joining..... \n");
	pthread_join(thread[1], (void **)&status);
	printf("return thread 1 %d\n", status);
	pthread_join(thread[0], (void **)&status);
	printf("return thread 0 %d\n", status);

	pthread_mutex_destroy(&mutexvar);
	pthread_cond_destroy(&condvar);
	return 0;
}
