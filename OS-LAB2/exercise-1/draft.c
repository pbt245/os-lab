#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid;
    printf("Start of main... PID: %d\n", getpid()); // print the parent's PID
    fflush(stdout);

    pid = fork();

    if (pid > 0)
    {
        /* parent process */
        printf("Parent section... PID: %d, Child PID: %d\n", getpid(), pid);
        fflush(stdout);
    }
    else if (pid == 0)
    {
        /* child process */
        printf("\nfork created... Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        fflush(stdout);
    }
    else
    {
        /* fork creation failed */
        printf("\nfork creation failed!!!\n");
        fflush(stdout);
    }

    return 0;
}