#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main( int argc, char *argv[] ) {

    if( argc < 2 ) {
        /* Nicht genügend Argumente */
        printf("Usage: synchronize <path>\n");
        return EXIT_SUCCESS;
    }

    DIR* dir = opendir("mydir");
    if (dir)
    {
        /* Verzeichnis existiert */

        // Starte Reader Thread
        // Starte Compression Threads

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