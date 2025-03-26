#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_MOVIES 1682

void compute_average(const char *filename, double *shm_ptr, int offset)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("fopen");
        exit(1); // 1 = fail, 0 = success
    }

    // init arrays index 1 -> 1682
    double sum[MAX_MOVIES + 1] = {0};
    int count[MAX_MOVIES + 1] = {0};

    int userID, movieID;
    double rating;
    long timeStamp;

    // read line
    while (fscanf(fp, "%d\t%d\t%lf\t%ld", &userID, &movieID, &rating, &timeStamp) == 4)
    {
        if (movieID >= 1 && movieID <= MAX_MOVIES)
        {
            sum[movieID] += rating;
            count[movieID]++;
        }
    }
    fclose(fp);

    // store to shm
    for (int i = 1; i <= MAX_MOVIES; i++)
    {
        if (count[i] > 0)
            shm_ptr[offset + i] = sum[i] / count[i];
        else
            shm_ptr[offset + i] = 0.0;
    }
}

int main()
{
    int shmid = shmget((__key_t)0, 2 * (MAX_MOVIES + 1) * sizeof(double), 0666 | IPC_CREAT); // param: private key, 2 arrays, chmod
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    // attach the shm
    double *shm_ptr = (double *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // 1st child process
    pid_t pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork1");
        exit(1);
    }
    if (pid1 == 0)
    {
        compute_average("data/movie-100k_1.txt", shm_ptr, 0);
        exit(0);
    }

    // 2nd child
    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork2");
        exit(1);
    }
    if (pid2 == 0)
    {
        compute_average("data/movie-100k_2.txt", shm_ptr, MAX_MOVIES + 1);
        exit(0);
    }

    // p waits 2 c to finish
    wait(NULL);
    wait(NULL);

    // output to txt file
    FILE *out_fp = fopen("output.txt", "w");
    if (!out_fp)
    {
        perror("fopen");
        exit(1);
    }

    fprintf(out_fp, "===== AVERAGE RATING in 1.txt =====\n");
    for (int i = 1; i <= MAX_MOVIES; i++)
    {
        if (shm_ptr[i] > 0.0)
        {
            fprintf(out_fp, "Movie %d: %.2f\n", i, shm_ptr[i]);
        }
    }

    fprintf(out_fp, "\n===== AVERAGE RATING in 2.txt =====\n");
    for (int i = MAX_MOVIES + 1; i < 2 * (MAX_MOVIES + 1); i++)
    {
        if (shm_ptr[i] > 0.0)
        {
            fprintf(out_fp, "Movie %d: %.2f\n", i - MAX_MOVIES, shm_ptr[i]);
        }
    }

    fclose(out_fp);

    // detach and rm
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL); // remove id

    return 0;
}
