#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include "threads.h"

#define NTHREADS 4

int main( int argc, char *argv[] ) {

    if( argc < 2 ) {
        /* Nicht genügend Argumente */
        printf("Usage: synchronize <path>\n");
        return EXIT_SUCCESS;
    }

    DIR* dir = opendir(argv[1]);
    if (dir)
    {
        /* Verzeichnis existiert */

        // Initialisierung
        MutexQueue *mutexQueue = mutexQueueInit();
        time_t start_t, end_t;
        double diff_t;

        // Starte Zeitmessung
        time(&start_t);

        // Starte Reader Thread
        pthread_t producer;
        if (pthread_create(&producer, NULL, readerThread, mutexQueue)) {
            perror("Fehler beim Starten des Erzeuger-Threads: ");
        }

        // Starte Compression Threads
        pthread_t consumers[NTHREADS];
        for (int i = 0; i < NTHREADS; i++) {
            comprThreadArg *arg = malloc(sizeof(comprThreadArg));
            if(arg) {
                arg->id = i+1;
                arg->mutexQueue = mutexQueue;
                if (pthread_create(&(consumers[i]), NULL, compressionThread, arg)) {
                    perror("Fehler beim Starten der Verbraucher-Threads: ");
                }
            } else {
                printf("Fehler beim Erzeugen eines Commpression-Thread Arguments\n");
                return EXIT_FAILURE;
            }
        }

        // Warten auf Ende der der Threads
        pthread_join(producer, NULL);
        for (int i = 0; i < NTHREADS; i++) {
            pthread_join(consumers[i], NULL);
        }
        printf("Alle Threads beendet.\n");

        // Ende Zeitmessung
        time(&end_t);

        // Aufräumen
        Cleanup(mutexQueue);

        // Ausgabe Laufzeit
        diff_t = difftime(end_t, start_t);
        printf("Laufzeit = %f\n", diff_t);

    }
    else if (ENOENT == errno)
    {
        /* Verzeichnis existiert nicht */
        perror("Verzeichnis existiert nicht: ");
        return EXIT_FAILURE;

    }
    else
    {
        /* anderer Fehler */
        perror("Fehler beim Öffnen des Verzeichnises: ");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
