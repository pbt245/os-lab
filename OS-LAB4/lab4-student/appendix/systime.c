#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

int main()
{
    struct timespec ts;
    char buffer[22];
    const int bufsize = 21;
    syscall(SYS_clock_gettime, CLOCK_REALTIME, &ts);
    strftime(buffer, bufsize, "%Y-%m-%d %H:%M:%S", gmtime(&ts.tv_sec));
    printf("%s\n", buffer);
    return 0;
}