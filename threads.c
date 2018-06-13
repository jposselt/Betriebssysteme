#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "threads.h"
#include "tools.h"

const char ignore[] = "compr";

/**
 *
 * @param job
 */
void deleteJob(Job *job) {
    free(job->path);
    free(job->content);
    free(job);
}

char *getFullPath(const char *base, const char *name) {
    char *realBase = realpath(base, NULL);
    char *fullPath = malloc(strlen(realBase) + strlen(name) + 2); // Test
    strcpy(fullPath, realBase);
    strcat(fullPath, "/");
    strcat(fullPath, name);
    free(realBase);
    return fullPath;
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

    struct dirent *dir;
    while ((dir = readdir(in->directory)) != NULL) {

        /* Nur reguläre Dateien anfassen */
        struct stat path_stat;
        char *fullPath = getFullPath(in->basename, dir->d_name);
        stat(fullPath, &path_stat);
        if(S_ISREG(path_stat.st_mode) && strcmp(get_filename_ext(fullPath), ignore) ) {

            // ...

        }

        free(fullPath);
    }

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
