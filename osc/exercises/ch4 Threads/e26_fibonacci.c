#include <stdio.h>
#include <pthread.h>

int num;
int fibs[1000];
void *runner(void *param);
int main(void)
{
    printf("Please input the number of fibonacci numbers you would print out:");
    scanf("%d", &num);

    pthread_t pid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&pid, &attr, runner, NULL);

    pthread_join(pid, NULL);

    for (int i = 0; i < num; i++)
    {
        printf("%d,\t", fibs[i]);
    }
    return 0;
}

void *runner(void *param)
{
    for (int i = 0; i < num; i++)
    {
        if (i == 0)
            fibs[i] = 1;
        else if (i == 1)
            fibs[i] = 1;
        else
        {
            fibs[i] = fibs[i - 1] + fibs[i - 2];
        }
    }
    pthread_exit(0);
}