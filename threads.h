#ifndef SYNCHRONISATION_THREADS_H
#define SYNCHRONISATION_THREADS_H

#include "mutexQueue.h"

typedef struct Job {
    char *path;
    char *content;
} Job;

typedef struct comprThreadArg {
    int id;
    MutexQueue *mutexQueue;
} comprThreadArg;

void deleteJob(Job *job);

void* readerThread(void *arg);
void* compressionThread(void *arg);

#endif //SYNCHRONISATION_THREADS_H
