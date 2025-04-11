#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock
{                               /* TODO: implement the structure */
    volatile unsigned int seq;  // seq counter
    pthread_mutex_t write_lock; // mutex for writer
    int data;                   // shared memory
} pthread_seqlock_t;z

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
    /* TODO: ... */
    if (!rw)
        return;
    rw->seq = 0;
    pthread_mutex_init(&rw->write_lock, NULL);
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
    /* TODO: ... */
    if (!rw)
        return;
    pthread_mutex_lock(&rw->write_lock);
    ++rw->seq; // make odd -> write stars
}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
    /* TODO: ... */
    if (!rw)
        return;
    ++rw->seq; // back to even -> writer ends
    pthread_mutex_unlock(&rw->write_lock);
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
    /* TODO: ... */
    if (!rw)
    {
        return 0;
    }
    unsigned seq1, seq2;
    do
    {
        seq1 = rw->seq;
        if (seq1 % 2 != 0)
            continue; // writer active
        // simulate read window here
        seq2 = rw->seq;
    } while (seq1 != seq2 || (seq2 % 2)); // retry if changed or writer arrived
    return 1;
}

static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
    /* TODO: ... */

    return 0;
}
