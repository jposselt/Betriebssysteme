#ifndef SYNCHRONISATION_MUTEXQUEUE_H
#define SYNCHRONISATION_MUTEXQUEUE_H

#include "queue.h"

typedef struct MutexQueue
{
    pthread_mutex_t *mutex;
    pthread_cond_t *notEmpty;
    int empty;
    Queue queue;
} MutexQueue;

MutexQueue *mutexQueueInit(void);
void Cleanup(MutexQueue *mutexQueue);

#endif //SYNCHRONISATION_MUTEXQUEUE_H
