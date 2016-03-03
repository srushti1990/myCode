/*
This solves the reentrance problem of the other program. Here, global values are removed from the 
function scope and thus the program becomes reentrant.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char arr[300];

struct arguments{
	char ch;
	int indval;
}argval[15];

void *myFunc(void *data)
{
	struct arguments* arg = (struct arguments *)data;
	char ch = arg->ch;
	int indval = arg->indval;
	int i = 0;
	if(indval >= sizeof(arr))
	{
		printf("\n No storage: Array full \n");
	}
	for(i = 0; i < 20; i++)
	{
		arr[indval] = ch;
		(indval)++;
		printf("Thread: %c - The index value is: %d\n", ch, indval);
	}	
}

int main()
{
	pthread_t thread[15];
	int thread_id;
	int status;
	char a = '1', b = '2', c = '3', d = '4', e = '5', f = '6', g = '7', h = '8', i = '9', j = 'a', k = 'b', l = 'c', m = 'd', n = 'e', o = 'f';
	argval[0].indval = 0;
	argval[0].ch = a;
	thread_id = pthread_create(&thread[0], NULL, myFunc, (void *)&argval[0]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[1].indval = 20;
	argval[1].ch = b;
	thread_id = pthread_create(&thread[1], NULL, myFunc, (void *)&argval[1]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[2].indval = 40;
	argval[2].ch = c;
	thread_id = pthread_create(&thread[2], NULL, myFunc, (void *)&argval[2]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[3].indval = 60;
	argval[3].ch = d;
	thread_id = pthread_create(&thread[3], NULL, myFunc, (void *)&argval[3]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}	
	argval[4].indval = 80;
	argval[4].ch = e;
	thread_id = pthread_create(&thread[4], NULL, myFunc, (void *)&argval[4]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[5].indval = 100;
	argval[5].ch = f;
	thread_id = pthread_create(&thread[5], NULL, myFunc, (void *)&argval[5]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[6].indval = 120;
	argval[6].ch = g;
	thread_id = pthread_create(&thread[6], NULL, myFunc, (void *)&argval[6]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[7].indval = 140;
	argval[7].ch = h;
	thread_id = pthread_create(&thread[7], NULL, myFunc, (void *)&argval[7]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[8].indval = 160;
	argval[8].ch = i;
	thread_id = pthread_create(&thread[8], NULL, myFunc, (void *)&argval[8]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[9].indval = 180;
	argval[9].ch = j;
	thread_id = pthread_create(&thread[9], NULL, myFunc, (void *)&argval[9]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[10].indval = 200;
	argval[10].ch = k;
	thread_id = pthread_create(&thread[10], NULL, myFunc, (void *)&argval[10]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[11].indval = 220;
	argval[11].ch = l;
	thread_id = pthread_create(&thread[11], NULL, myFunc, (void *)&argval[11]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[12].indval = 240;
	argval[12].ch = m;
	thread_id = pthread_create(&thread[12], NULL, myFunc, (void *)&argval[12]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[13].indval = 260;
	argval[13].ch = n;
	thread_id = pthread_create(&thread[13], NULL, myFunc, (void *)&argval[13]);
	if(thread_id < 0)
	{
		perror("Thread create error");
		exit(0);
	}
	argval[14].indval = 280;
	argval[14].ch = o;
	thread_id = pthread_create(&thread[14], NULL, myFunc, (void *)&argval[14]);
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
