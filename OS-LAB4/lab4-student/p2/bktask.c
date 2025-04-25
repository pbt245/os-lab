#include "bktpool.h"
#include <stdlib.h>

struct bktask_t *bktask_get_byid(unsigned int bktaskid)
{
    struct bktask_t *ptask = bktask;

    if (bktaskid < 0 || bktaskid > bktask_sz)
        return NULL;

    if (ptask == NULL)
        return NULL;

    while (ptask != NULL)
    {
        if (ptask->bktaskid == bktaskid)
            return ptask;

        ptask = ptask->tnext;
    }

    return NULL;
}

int bktask_init(unsigned int *bktaskid, void *func, void *arg)
{
    struct bktask_t *new_task = malloc(sizeof(struct bktask_t));
    if (new_task == NULL)
        return -1;

    *bktaskid = taskid_seed++;
    bktask_sz++;

    new_task->func = func;
    new_task->arg = arg;
    new_task->bktaskid = *bktaskid;
    new_task->tnext = bktask;

    bktask = new_task;

    return 0;
}

int bktask_destroy(unsigned int bktaskid)
{
    struct bktask_t *ptask = bktask;
    struct bktask_t *prev = NULL;

    while (ptask != NULL)
    {
        if (ptask->bktaskid == bktaskid)
        {
            if (prev == NULL)
                bktask = ptask->tnext;
            else
                prev->tnext = ptask->tnext;

            free(ptask);
            bktask_sz--;
            return 0;
        }
        prev = ptask;
        ptask = ptask->tnext;
    }

    return -1;
}