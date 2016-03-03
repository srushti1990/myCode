/*
This program depicts the reentrant problem that programs face in the multi-threaded environment. Here,
the intended values are not assigned to the arrays run by many threads. So, inconsistency is observed
in the output. This is solved by another program.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int ind = 0;
char arr[300];

void *myFunc(void *data)
{
	char ch = *((char *)data);
	int i = 0;
	if(ind >= sizeof(arr))
	{
		printf("\n No storage: Array full \n");
	}
	for(i = 0; i < 20; i++)
	{
		arr[ind] = ch;
		ind++;
		printf("Thread: %c - The index value is: %d\n", ch, ind);
	}
}

int main()
{
	pthread_t thread[15];
	int thread_id;
	int status;
	char a = '1', b = '2', c = '3', d = '4', e = '5', f = '6', g = '7', h = '8', i = '9', j = 'a', k = 'b', l = 'c', m = 'd', n = 'e', o = 'f';
	thread_id = pthread_create(&thread[0], NULL, myFunc, (void *)&a);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[1], NULL, myFunc, (void *)&b);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[2], NULL, myFunc, (void *)&c);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[3], NULL, myFunc, (void *)&d);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[4], NULL, myFunc, (void *)&e);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[5], NULL, myFunc, (void *)&f);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[6], NULL, myFunc, (void *)&g);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[7], NULL, myFunc, (void *)&h);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[8], NULL, myFunc, (void *)&i);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[9], NULL, myFunc, (void *)&j);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[10], NULL, myFunc, (void *)&k);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[11], NULL, myFunc, (void *)&l);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[12], NULL, myFunc, (void *)&m);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[13], NULL, myFunc, (void *)&n);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	thread_id = pthread_create(&thread[14], NULL, myFunc, (void *)&o);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}

	pthread_join(thread[0], (void **)&status);
	printf("return thread 0 %d\n", status);
	pthread_join(thread[1], (void **)&status);
	printf("return thread 1 %d\n", status);
	pthread_join(thread[2], (void **)&status);
	printf("return thread 2 %d\n", status);
	pthread_join(thread[3], (void **)&status);
	printf("return thread 3 %d\n", status);
	pthread_join(thread[4], (void **)&status);
	printf("return thread 4 %d\n", status);
	pthread_join(thread[5], (void **)&status);
	printf("return thread 5 %d\n", status);
	pthread_join(thread[6], (void **)&status);
	printf("return thread 6 %d\n", status);
	pthread_join(thread[7], (void **)&status);
	printf("return thread 7 %d\n", status);
	pthread_join(thread[8], (void **)&status);
	printf("return thread 8 %d\n", status);
	pthread_join(thread[9], (void **)&status);
	printf("return thread 9 %d\n", status);
	pthread_join(thread[10], (void **)&status);
	printf("return thread 10 %d\n", status);
	pthread_join(thread[11], (void **)&status);
	printf("return thread 11 %d\n", status);
	pthread_join(thread[12], (void **)&status);
	printf("return thread 12 %d\n", status);
	pthread_join(thread[13], (void **)&status);
	printf("return thread 13 %d\n", status);
	pthread_join(thread[14], (void **)&status);
	printf("return thread 14 %d\n", status);
	return 0;
}
