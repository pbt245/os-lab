#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 1682

double sum_ratings[MAX_MOVIES + 1] = {0};
int count_ratings[MAX_MOVIES + 1] = {0};

// Mutex lock for thread safety
pthread_mutex_t lock;

void *compute_average(void *arg)
{
    char *filename = (char *)arg;
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("open file fail");
        pthread_exit(NULL);
    }

    int userID, movieID;
    double rating;
    long timestamp;

    while (fscanf(fp, "%d\t%d\t%lf\t%ld", &userID, &movieID, &rating, &timestamp) == 4)
    {
        if (movieID >= 1 && movieID <= MAX_MOVIES)
        {
            pthread_mutex_lock(&lock); // lock before updating global arrays
            sum_ratings[movieID] += rating;
            count_ratings[movieID]++;
            pthread_mutex_unlock(&lock); // unlock after update
        }
    }

    fclose(fp);
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;

    // init mutex
    pthread_mutex_init(&lock, NULL);

    // 2 threads
    pthread_create(&thread1, NULL, compute_average, "data/movie-100k_1.txt");
    pthread_create(&thread2, NULL, compute_average, "data/movie-100k_2.txt");

    // wait both threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    FILE *out_fp = fopen("output.txt", "w");
    if (!out_fp)
    {
        perror("open output file fail");
        exit(1);
    }

    fprintf(out_fp, "MovieID\tAverage Rating\n");
    for (int i = 1; i <= MAX_MOVIES; i++)
    {
        if (count_ratings[i] > 0)
        {
            double avg = sum_ratings[i] / count_ratings[i];
            fprintf(out_fp, "%d\t%.2f\n", i, avg);
        }
    }

    fclose(out_fp);


    pthread_mutex_destroy(&lock);
    printf("Results written to output.txt\n");
    return 0;
}
