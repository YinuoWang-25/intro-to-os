**3.1** Using the program shown in Figure 3.30, explain what the output will be at LINE A.

```c
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int value = 5;
int main()
{
    pid t pid;
    pid = fork();
    if (pid == 0) { /* child process */
        value += 15;
        return 0;
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d",value); /* LINE A */
        return 0;
    }
}
```

**Answer**: 5

<br>

**3.2** Including the initial parent process, how many processes are created by
the program shown in Figure 3.31?

```c
#include <stdio.h>
#include <unistd.h>
int main()
{
    /* fork a child process */
    fork();
    /* fork another child process */
    fork();
    /* and fork another */
    fork();
    return 0;
}
```

**Answer**: There are 8 processes created.

<br>

**3.3** Original versions of Apple’s mobile iOS operating system provided no means of concurrent processing. Discuss three major complications that concurrent processing adds to an operating system.

**Answer**: TBD

<br>

**3.4** The Sun UltraSPARC processor has multiple register sets. Describe what
happens when a context switch occurs if the new context is already
loaded into one of the register sets. What happens if the new context is
in memory rather than in a register set and all the register sets are in
use?
