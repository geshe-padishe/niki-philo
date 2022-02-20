#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
	printf("TEST FROM THREADS\n");
	sleep(3);
	printf("Ending Thread\n");
}

void *routine2()
{
	int i;
	for (i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv)
{
	pthread_t t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine2, NULL) != 0)
		return (-1);
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
		return (-1);
	if (pthread_join(t1, NULL) != 0)
		return (-1);
	if (pthread_join(t2, NULL) != 0)
		return (-1);
	pthread_mutex_destroy(&mutex);
	printf("mails = %d\n", mails);
	return (0);
}
