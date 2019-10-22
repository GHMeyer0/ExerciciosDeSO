#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int count = 0;
sem_t lock;

void * ThreadAdd(void * a)
{
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
        sem_wait(&lock);
        tmp = count;      /* copiar o contador global localmente */
        tmp = tmp+1;      /* incrementar a cópia local */
        count = tmp;      /* armazene o valor do contador global */ 
        sem_post(&lock);
    }
}

int main(int argc, char * argv[])
{
    sem_init(&lock, 0, 1);
    pthread_t tid1, tid2;

    if(pthread_create(&tid1, NULL, ThreadAdd, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadAdd, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* aguardar thread 1 terminar */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* aguardar thread 2 terminar */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (count < 2 * NITER) 
        printf("\n BOOM! count is [%d], should be %d\n", count, 2*NITER);
    else
        printf("\n OK! count is [%d]\n", count);
  
    pthread_exit(NULL);
}