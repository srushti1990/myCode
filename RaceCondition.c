/*
This is a program demonstrating race condition. According to the programmer's logic, the index value of
the array and the element value have to be the same. But due to the sleep() function, the desired result
is not observed.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int ind = 0;
int arr[50];

void *myFuncA(void *data)
{
	char t = *((char *)data);
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		if(ind >= sizeof(arr)/sizeof(int))
		{
			printf("\n No storage: Array full \n");
			break;
		}
		if(/*i == 9 || i == 20 ||*/ i == 35)	sleep(5);
		arr[ind] = i;
		printf("Thread %c: - The index value is: %d and the array value is: %d\n", t, ind, arr[ind]);
		ind++;
	}
}

void *myFuncB(void *data)
{
	char t = *((char *)data);
	int i;
	for(i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		if(i == 1 || i == 25 || i == 40)	sleep(3);
		ind--;
		printf("Thread %c: - The index value is: %d and the array value is: %d\n", t, ind, arr[ind]);
		arr[ind] = -1;
		if(ind < 0)
		{
			printf("\n Nothing stored: Array empty \n");
			break;
		}
	}
}

int main()
{
	pthread_t thread[2];
	int thread_id;
	int status;
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
	pthread_join(thread[1], (void **)&status);
	printf("return thread 1 %d\n", status);
	pthread_join(thread[0], (void **)&status);
	printf("return thread 0 %d\n", status);
	return 0;
}
