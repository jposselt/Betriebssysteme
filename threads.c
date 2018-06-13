#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

#include "threads.h"
#include "tools.h"
#include "miniz.h"

const char comprExt[] = "compr";

/**
 * Gibt den belegten Speicher frei
 * @param job
 */
void deleteJob(Job *job) {
    free(job->path);
    free(job->content);
    free(job);
}

/**
 * Bestimmt den vollständigen Pfad einer Datei
 *
 * Der zurückgegebene Zeiger muss vom Aufrufer mit free() freigegeben werden.
 *
 * @param base Pfad des Verzeichnises in dem sich die Datei befindet
 * @param name Name der Datei
 * @return Vollständiger Pfad der Datei
 */
char *getFullPath(const char *base, const char *name) {
    char *realBase = realpath(base, NULL);
    char *fullPath = malloc(strlen(realBase) + strlen(name) + 2);
    if (!fullPath) {
        printf("getFullPath: Fehler beim Speicherallozieren\n");
        exit(EXIT_FAILURE);
    }
    strcpy(fullPath, realBase);
    strcat(fullPath, "/");
    strcat(fullPath, name);
    free(realBase);
    return fullPath;
}

/**
 *
 * @param filePath
 * @return
 */
char *getCompressedFileName(const char *filePath) {
    char *comprFile = malloc(strlen(filePath) + strlen(comprExt) + 2);
    if (!comprFile) {
        printf("getCompressedFileName: Fehler beim Speicherallozieren\n");
        exit(EXIT_FAILURE);
    }
    strcpy(comprFile, filePath);
    strcat(comprFile, ".");
    strcat(comprFile, comprExt);

    return comprFile;
}

/**
 * Thread-Funktion zum Einfügen von Jobs in die Warteschlange
 * @param arg readerThreadArg Struktur
 * @return NULL
 */
void *readerThread(void *arg) {
    readerThreadArg *in = (readerThreadArg *) arg;
    MutexQueue *mutexQueue = in->mutexQueue;

    printf("Reader thread gestartet.\n");

    struct dirent *dir;
    while ((dir = readdir(in->directory)) != NULL) {

        /* Nur reguläre, unkomprimierte Dateien anfassen */
        struct stat path_stat;
        char *fullPath = getFullPath(in->basename, dir->d_name); // Test
        stat(fullPath, &path_stat);
        if( (S_ISREG(path_stat.st_mode) != 0) && (strcmp(get_filename_ext(fullPath), comprExt) != 0) ) {

            printf("readerThread: Bearbeite %s\n", dir->d_name);

            // Erzeuge Job
            Job *job = malloc(sizeof(Job));
            if (!job) {
                printf("readerThread: Fehler beim Speicherallozieren\n");
                exit(EXIT_FAILURE);
            }
            job->path = strdup(fullPath);
            job->content = get_file_content(fullPath);

            // Sperre anfordern
            if (pthread_mutex_lock(mutexQueue->mutex)) {
                perror("Fehler beim Sperren des Mutex: ");
                return NULL;
            }

            // Job hinzufügen
            if ( !(queue_insert(mutexQueue->queue, job)) ) {
                printf("readerThread: Konnte Job nicht zu Queue hinzufügen\n");
            }
            mutexQueue->empty = 0;

            // Signal senden
            if (pthread_cond_signal(mutexQueue->notEmpty)) {
                perror("Fehler beim Senden eines Signals: ");
            }

            // Sperre lösen
            if (pthread_mutex_unlock(mutexQueue->mutex)) {
                perror("Fehler beim Entsperren des Mutex: ");
                return NULL;
            }

        }

        free(fullPath);
    }

    // Sperre anfordern
    if (pthread_mutex_lock(mutexQueue->mutex)) {
        perror("Fehler beim Sperren des Mutex: ");
        return NULL;
    }

    // Marker, dass Produzent fertig ist
    mutexQueue->running = 0;

    // Signal senden
    if (pthread_cond_signal(mutexQueue->notEmpty)) {
        perror("Fehler beim Senden eines Signals: ");
    }

    // Sperre lösen
    if (pthread_mutex_unlock(mutexQueue->mutex)) {
        perror("Fehler beim Entsperren des Mutex: ");
        return NULL;
    }

    printf("Reader thread beendet.\n");

    return NULL;
}

/**
 * Thread zum Komprimieren von Dateien
 * @param arg comprThreadArg Struktur
 * @return NULL
 */
void *compressionThread(void *arg) {
    comprThreadArg *in = (comprThreadArg *) arg;
    Job *job;
    int loop = 1;

    // Kopiere Argumente
    int id = in->id;
    MutexQueue *mutexQueue = in->mutexQueue;

    // Argument freigeben
    free(arg);

    printf("Compression thread Nr. %d gestartet.\n", id);

    while (loop) {
        // Sperre anfordern
        if (pthread_mutex_lock(mutexQueue->mutex)) {
            perror("Fehler beim Sperren des Mutex: ");
            return NULL;
        }

        while (mutexQueue->empty) {
            printf("Compression thread Nr. %d: Warte auf Daten\n", id);
            pthread_cond_wait(mutexQueue->notEmpty, mutexQueue->mutex);
        }

        // Job aus Queue holen
        job = (Job *) queue_head(mutexQueue->queue);
        queue_delete(mutexQueue->queue);

        if (queue_empty(mutexQueue->queue)) { // Queue leer
            mutexQueue->empty = 1;
            if ( !(mutexQueue->running) ) {   // Erzeuger beendet
                loop = 0;
                /*
                 * Queue ist eigentlich leer, aber wir müssen ein letztes
                 * mal die Wartebedinung überwinden
                 */
                mutexQueue->empty = 0;
                pthread_cond_signal(mutexQueue->notEmpty);
            }
        } else {                              // Noch Jobs in der Queue
            mutexQueue->empty = 0;
            pthread_cond_signal(mutexQueue->notEmpty);
        }

        // Sperre lösen
        if (pthread_mutex_unlock(mutexQueue->mutex)) {
            perror("Fehler beim Entsperren des Mutex: ");
            return NULL;
        }

        // Job vorhanden
        if (job) {

            printf("Compression thread Nr. %d: Komprimiere %s\n", id, job->path);

            // Schreibe komprimierten Inhalt in Datei
            Result *result = compress_string(job->content);
            if (result) {
                char *name = getCompressedFileName(job->path);
                write_file(name, result->data);
                free(name);
                free(result->data);
                free(result);
            }

            // Job löschen
            deleteJob(job);

            sleep(3);
        }

    }

    printf("Compression thread Nr. %d beendet.\n", id);
    return NULL;
}
