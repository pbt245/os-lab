#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define FILENAME "shared_memory.txt"
#define FILESIZE 1024 // 1 KB

void create_file(const char *filename, int size)
{
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    if (ftruncate(fd, size) == -1)
    {
        perror("ftruncate");
        close(fd);
        exit(1);
    }
    close(fd);
}

int main()
{
    // create and truncate file size
    create_file(FILENAME, FILESIZE);

    // open read write
    int fd = open(FILENAME, O_RDWR);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    // map to mem
    char *mapped_mem = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        exit(1);
    }
    close(fd);

    // fork process
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork fail");
        exit(1);
    }
    else if (pid == 0) // child
    {             
        printf("child reads from shm: %s\n", mapped_mem);
    }
    else // parent
    {
        const char *message = "Reply from parent ";
        strncpy(mapped_mem, message, FILESIZE);
        printf("parent writes to shm \n");
        wait(NULL);
    }

    munmap(mapped_mem, FILESIZE);
    unlink(FILENAME);

    return 0;
}
