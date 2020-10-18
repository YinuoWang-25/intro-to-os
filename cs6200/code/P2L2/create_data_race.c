#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

/*
The output might be:
Thread number 3
Thread number 4
Thread number 4
Thread number 4

because of data race on i
*/

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
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&tid[i], NULL, threadFunc, &i);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }

    return 0;
}