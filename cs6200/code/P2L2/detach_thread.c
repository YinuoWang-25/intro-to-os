#include <stdio.h>
#include <pthread.h>

void *foo(void *args)
{
    /* thread main */
    printf("Foobar !\n");
    pthread_exit(0);
}

int main(void)
{
    int i;
    pthread_t tid;

    pthread_attr_t attr;
    pthread_attr_init(&attr); /* required */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_create(NULL, &attr, foo, NULL);
    return 0;
}