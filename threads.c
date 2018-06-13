#include <stdlib.h>
#include <stdio.h>
#include "threads.h"
//#include "tools.h"

/**
 *
 * @param job
 */
void deleteJob(Job *job) {
    free(job->path);
    free(job->content);
    free(job);
}

/**
 *
 * @param arg
 * @return
 */
void *readerThread(void *arg) {
    readerThreadArg *in = (readerThreadArg *) arg;

    MutexQueue *mq = in->mutexQueue;

    printf("Reader thread gestartet.\n");



    return NULL;
}

/**
 * Thread zum Komprimieren von Dateien
 * @param arg
 * @return
 */
void *compressionThread(void *arg) {
    comprThreadArg *in = (comprThreadArg *) arg;

    // Kopiere Argumente
    int id = in->id;
    MutexQueue *mutexQueue = in->mutexQueue;

    // Argument freigeben
    free(arg);

    printf("Compression thread Nr. %d gestartet.\n", id);

    return NULL;
}
