#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define PERMS 0644
#define MSG_KEY 0x123

struct my_msgbuf
{
    long mtype;
    char mtext[200];
};

int msqid;

void *receive_messages(void *arg)
{
    struct my_msgbuf buf;
    while (1)
    {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 2, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Recived: %s\n", buf.mtext);
        if (strcmp(buf.mtext, "end") == 0)
        {
            break;
        }
    }
    pthread_exit(NULL);
}

void *send_messages(void *arg)
{
    struct my_msgbuf buf;
    buf.mtype = 1;
    while (1)
    {
        // printf("\n");
        fgets(buf.mtext, sizeof(buf.mtext), stdin);
        buf.mtext[strcspn(buf.mtext, "\n")] = 0;
        if (msgsnd(msqid, &buf, strlen(buf.mtext) + 1, 0) == -1)
        {
            perror("msgsnd");
        }
        if (strcmp(buf.mtext, "end") == 0)
        {
            break;
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t send_thread, recv_thread;
    if ((msqid = msgget(MSG_KEY, PERMS | IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }
    printf("Ready to send or recive message\n");
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_create(&send_thread, NULL, send_messages, NULL);

    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);

    printf("End chat.\n");
    return 0;
}
