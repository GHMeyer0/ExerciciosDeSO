#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
int n = 1;
sem_t lock, lock_two;

void  X(void *argp) {
	n = n * 16;
	sem_post(&lock); // libera o primeiro sinal
}
void Z(void *argp) {
	sem_wait(&lock);
	n = n + 40;
	sem_post(&lock_two);
}
void Y(void *argp) {
	sem_wait(&lock_two);
	n = n / 7;
}

int main(void) {
	int quantidades_de_testes = 1000;
	int resultados_incorretos = 0;
	
	// Laço para testar o programa na quantidade de vezes que foi definida na variavel "quantidades_de_testes"
	for (size_t i = 0; i < quantidades_de_testes; i++)
	{
		pthread_t t1, t2, t3;
		sem_init(&lock, 0, 0); // Inicializa primeiro sinal travado
		sem_init(&lock_two, 0, 0); // Inicializa segundo sinal travado

		int rc;
		rc = pthread_create(&t1, NULL, (void *)X, NULL);
		rc = pthread_create(&t2, NULL, (void *)Y, NULL);
		rc = pthread_create(&t3, NULL, (void *)Z, NULL);

		rc = pthread_join(t1, NULL);
		rc = pthread_join(t2, NULL);
		rc = pthread_join(t3, NULL);
		printf("n=%d\n", n);
		if (n != 8)
		{
			resultados_incorretos++;
		}
		n = 1;
	}
	printf("contador de erros = %d\n", resultados_incorretos);
	
	
	return 0;
}
