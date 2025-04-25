#define _GNU_SOURCE
#include "bktpool.h"
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

// #define DEBUG
#define INFO
#define WORK_THREAD

int bkwrk_worker(void *arg)
{
    sigset_t set;
    int sig;
    int s;
    int i = *((int *)arg);
    struct bkworker_t *wrk = &worker[i];

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGQUIT);

#ifdef DEBUG
    fprintf(stderr, "worker %i start living tid %d \n", i, getpid());
    fflush(stderr);
#endif

    while (1)
    {
        s = sigwait(&set, &sig);
        if (s != 0)
            continue;

#ifdef INFO
        fprintf(stderr, "worker wake %d up\n", i);
#endif

        if (wrk->func != NULL)
            wrk->func(wrk->arg);

        wrkid_busy[i] = 0;
        worker[i].func = NULL;
        worker[i].arg = NULL;
        worker[i].bktaskid = -1;
    }
}

int bktask_assign_worker(unsigned int bktaskid, unsigned int wrkid)
{
    if (wrkid < 0 || wrkid > MAX_WORKER)
        return -1;

    struct bktask_t *tsk = bktask_get_byid(bktaskid);

    if (tsk == NULL)
        return -1;

    wrkid_busy[wrkid] = 1;
    worker[wrkid].func = tsk->func;
    worker[wrkid].arg = tsk->arg;
    worker[wrkid].bktaskid = bktaskid;

    printf("Assign tsk %d wrk %d \n", tsk->bktaskid, wrkid);
    return 0;
}

int bkwrk_create_worker()
{
    unsigned int i;

    for (i = 0; i < MAX_WORKER; i++)
    {
        wrkid_busy[i] = 0;
        wrkid_tid[i] = -1;

#ifdef WORK_THREAD
        void **child_stack = (void **)malloc(STACK_SIZE);
        if (child_stack == NULL)
        {
            fprintf(stderr, "Failed to allocate stack for worker %u\n", i);
            return -1;
        }

        unsigned int wrkid = i;
        sigset_t set;

        sigemptyset(&set);
        sigaddset(&set, SIGQUIT);
        sigaddset(&set, SIGUSR1);
        sigprocmask(SIG_BLOCK, &set, NULL);

        void *stack_top = child_stack + STACK_SIZE;

        wrkid_tid[i] = clone(&bkwrk_worker, stack_top, CLONE_VM | CLONE_FILES, (void *)&wrkid);
        if (wrkid_tid[i] == -1)
        {
            fprintf(stderr, "Failed to create worker %u\n", i);
            free(child_stack);
            return -1;
        }

#ifdef INFO
        fprintf(stderr, "bkwrk_create_worker got worker %u\n", wrkid_tid[i]);
#endif

        usleep(100);
#else
        /* TODO: Implement fork version of create worker */
#endif
    }

    return 0;
}

int bkwrk_get_worker()
{
    for (unsigned int i = 0; i < MAX_WORKER; i++)
    {
        if (wrkid_busy[i] == 0)
        {
#ifdef DEBUG
            fprintf(stderr, "Selected worker %u (FIFO)\n", i);
#endif
            return i;
        }
    }

#ifdef DEBUG
    fprintf(stderr, "No available workers\n");
#endif
    return -1;
}

int bkwrk_dispatch_worker(unsigned int wrkid)
{
#ifdef WORK_THREAD
    unsigned int tid = wrkid_tid[wrkid];

    if (worker[wrkid].func == NULL)
        return -1;

#ifdef DEBUG
    fprintf(stderr, "brkwrk dispatch wrkid %d - send signal %u \n", wrkid, tid);
#endif

    syscall(SYS_tkill, tid, SIG_DISPATCH);
#else
    /* TODO: Implement fork version to signal worker process here */
#endif
}