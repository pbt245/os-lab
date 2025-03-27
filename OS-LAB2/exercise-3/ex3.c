#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_FILE "abc_fifo_name"

void rcv()
{
    char buffer[100];
    int fd = open(FIFO_FILE, O_RDONLY); // read only
    if (fd == -1)
    {
        perror("open fifo read fail");
        exit(1);
    }
    
    read(fd, buffer, sizeof(buffer));
    printf("Message received haha: %s\n", buffer);
    close(fd);
}

void fifo_snd(const char *message)
{
    int fd = open(FIFO_FILE, O_WRONLY); // write only
    if (fd == -1)
    {
        perror("open fifo write fail");
        exit(1);
    }

    write(fd, message, strlen(message) + 1);
    close(fd);
}

int main()
{
    if (mkfifo(FIFO_FILE, 0666) == -1)
    {
        perror("mkfifo fail");
        exit(1);
    }

    int pid = fork();

    if (pid == -1)
    {
        perror("fork fail");
        exit(1);
    }

    if (pid == 0) // child
    {
        fifo_snd("hey, yasuo");
        exit(0);
    }
    else // parent
    {
        rcv();
        wait(NULL);
    }

    unlink(FIFO_FILE); // remove so that can run multiple times
    return 0;
}
