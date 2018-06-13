#ifndef SYNCHRONISATION_THREADS_H
#define SYNCHRONISATION_THREADS_H

#include <dirent.h>
#include "mutexQueue.h"

typedef struct Job {
    char *path;
    char *content;
} Job;

typedef struct readerThreadArg {
    DIR *directory;
    char *basename;
    MutexQueue *mutexQueue;
} readerThreadArg;

typedef struct comprThreadArg {
    int id;
    MutexQueue *mutexQueue;
} comprThreadArg;

void deleteJob(Job *job);

void* readerThread(void *arg);
void* compressionThread(void *arg);

#endif //SYNCHRONISATION_THREADS_H
