#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
pthread_mutex_t mutex;

void* routine(void* arg)
{
	int index = *(int*)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++)
	{
		sum += primes[index + j];
	}
	//printf("%d ", primes[index]);
	//free(arg);
	*(int*)arg = sum;
    return (arg);
}

int main(int argc, char **argv)
{
    pthread_t th[2];
	//pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 2; i++)
	{
    	int* a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
        	perror("failed to create thread");
	}
	int global_sum = 0;
    for (int i = 0; i < 2; i++)
	{
    	int *r;
		if (pthread_join(th[i], (void **)&r) != 0)
			perror("failed to create thread");
		global_sum += *r;
		free(r);
	}
	printf("global sum %d", global_sum);
    return 0;
}