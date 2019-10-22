#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 20000
int n;
sem_t lock;

void f1(void *argp) {
	int i, temp;
	for (i = 0; i < MAX; i++) {
		sem_wait(&lock);
        temp = n;
		temp++;
		n = temp;
        sem_post(&lock);
	}
}

void f2(void *argp) {
	int i, temp;
	for (i = 0; i < MAX; i++) {
		sem_wait(&lock);
        temp = n;
		temp--;
		n = temp;
        sem_post(&lock);
	}
}
int main(void) {
    sem_init(&lock, 0, 1);
	pthread_t t1, t2;
	int rc;
	n = 0;
	rc = pthread_create(&t1, NULL, (void *)f1, NULL);
	rc = pthread_create(&t2, NULL, (void *)f2, NULL);
	rc = pthread_join(t1, NULL);
	rc = pthread_join(t2, NULL);
	printf("n=%d\n", n);
	return 0;
}
