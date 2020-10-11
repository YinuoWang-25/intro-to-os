#include <stdio.h>
#include <unistd.h>
// Create 16 process in total
int main()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        fork();
    }
    return 0;
}