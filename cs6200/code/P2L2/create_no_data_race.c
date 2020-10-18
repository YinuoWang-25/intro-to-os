#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *threadFunc(void *pArg)
{
    /* thread main */
    int *p = (int *)pArg;
    int myNum = *p;
    printf("Thread number %d\n", myNum);
    return 0;
}

int main(void)
{
    // int i;
    pthread_t tid[NUM_THREADS];
    int tNum[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        tNum[i] = i;
        pthread_create(&tid[i], NULL, threadFunc, &tNum[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}