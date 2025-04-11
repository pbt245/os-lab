#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void *write_buffer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }

        buffer[count++] = rand() % 100;
        printf("Produce: %d,	Buffer count: %d\n", buffer[count - 1], count);

        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *read_buffer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        while (count == 0)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }

        int item = buffer[--count];
        printf("Consume: %d,	Buffer count: %d\n", item, count);

        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main()
{
    pthread_t writer_thread, reader_thread;

    pthread_create(&writer_thread, NULL, write_buffer, NULL);
    pthread_create(&reader_thread, NULL, read_buffer, NULL);

    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread, NULL);

    return 0;
}
