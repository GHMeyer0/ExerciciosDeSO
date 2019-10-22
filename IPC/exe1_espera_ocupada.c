#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int count = 0;
int lock = 1;
void * ThreadAdd(void * a)
{
    int i, tmp;
    while (lock == 0); lock = 0;
    for(i = 0; i < NITER; i++)
    {
        tmp = count;      /* copiar o contador global localmente */
        tmp = tmp+1;      /* incrementar a cópia local */
        count = tmp;      /* armazene o valor do contador global */ 
    }
    lock = 1;
}

int main(int argc, char * argv[])
{
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