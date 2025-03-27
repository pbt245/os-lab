#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid1, pid2;

    // 1st child
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork fail");
        exit(1);
    }
    else if (pid1 == 0)
    {
        execl("./child1", "child1", NULL);
        perror("execl fail");
        exit(1);
    }

    // 2nd child
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork fail");
        exit(1);
    }
    else if (pid2 == 0)
    {
        execl("./child2", "child2", NULL);
        perror("execl fail");
        exit(1);
    }

    wait(NULL);
    wait(NULL);

    printf("Message from Parent: All done!!!\n");
    return 0;
}