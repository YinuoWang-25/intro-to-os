#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3 /* size of shared buffer */

int buffer[BUF_SIZE];                             /* shared buffer */
int add = 0;                                      /* place to add next element */
int rem = 0;                                      /* place to remove next element */
int num = 0;                                      /* number element in buffer */
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;    /* mutex lock for buffer */
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; /* consumer waits on cv */
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; /* producer waits on cv */

void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2; /* thread identifiers */
    int i;
    if (pthread_create(&tid1, NULL, producer, NULL) != 0)
    {
        fprintf(stderr, "Unable to create producer thread\n");
        exit(1);
    }
    if (pthread_create(&tid2, NULL, consumer, NULL) != 0)
    {
        fprintf(stderr, "Unable to create consumer thread\n");
        exit(1);
    }
    pthread_join(tid1, NULL); /* wait for producer to exit */
    pthread_join(tid2, NULL); /* wait for consumer to exit */
    printf("Parent quiting \n");
}

void *producer(void *param)
{
    int i;
    for (int i = 1; i <= 20; i++)
    {
        pthread_mutex_lock(&m);

        if (num > BUF_SIZE)
        {
            exit(1); /* buffer overflow */
        }
        while (num == BUF_SIZE)
        {
            pthread_cond_wait(&c_prod, &m); /* block if buffer is full */
        }
        buffer[add] = i; /* buffer not full, so add element */
        add = (add + 1) % BUF_SIZE;
        num++;
        printf("producer: inserted %d\n", i);
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_cons);
        fflush(stdout);
    }
    printf("Producer thread quiting \n");
    fflush(stdout);
    return 0;
}

void *consumer(void *param)
{
    int i;
    while (1)
    {
        pthread_mutex_lock(&m);

        if (num < 0)
        {
            exit(1); /* buffer underflow */
        }
        while (num == 0)
        {
            pthread_cond_wait(&c_cons, &m); /* block if buffer is empty */
        }
        i = buffer[rem]; /* buffer not empty, so remove element */
        rem = (rem + 1) % BUF_SIZE;
        num--;
        printf("Consume value %d\n", i);
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_prod);
        fflush(stdout);
    }
    return 0;
}