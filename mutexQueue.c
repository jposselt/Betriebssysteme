
#include <pthread.h>
#include "mutexQueue.h"

MutexQueue *mutexQueueInit(void) {
    MutexQueue *mutexQueue = (MutexQueue *) malloc(sizeof(MutexQueue));

    mutexQueue->queue = queue_create();
    mutexQueue->mutex = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
    pthread_mutex_init (mutexQueue->mutex, NULL);
    mutexQueue->notEmpty = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
    pthread_cond_init (mutexQueue->notEmpty, NULL);
    mutexQueue->empty = 1;

    return mutexQueue;
}

void Cleanup(MutexQueue *mutexQueue) {
    pthread_mutex_destroy (mutexQueue->mutex);
    free (mutexQueue->mutex);
    pthread_cond_destroy (mutexQueue->notEmpty);
    free (mutexQueue->notEmpty);
    queue_destroy(mutexQueue->queue);
    free(mutexQueue);
}
