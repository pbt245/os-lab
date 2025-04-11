#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int MAX_COUNT = 1e9;
static int count = 0;

// Declare a mutex to protect the shared variable 'count'
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

void *f_count(void *sid)
{
    int i;
    for (i = 0; i < MAX_COUNT; i++)
    {
        // Lock the mutex before accessing 'count'
        pthread_mutex_lock(&count_mutex);
        count = count + 1;
        // Unlock the mutex after modifying 'count'
        pthread_mutex_unlock(&count_mutex);
    }

    printf("Thread %s: holding %d \n", (char *)sid, count);
    return NULL;
}


int main() {
  pthread_t thread1, thread2;

  /* Create independent threads each of which will execute function */
  pthread_create( &thread1, NULL, &f_count, "1");
  pthread_create( &thread2, NULL, &f_count, "2");


  // Wait for thread th1 finish
  pthread_join( thread1, NULL);

  // Wait for thread th1 finish
  pthread_join( thread2, NULL);

  // Destroy the mutex
  pthread_mutex_destroy(&count_mutex);

  return 0;
}
