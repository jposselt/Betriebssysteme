#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#include <fcntl.h> /* fuer Kontrollfluss */
#include <unistd.h>

#include "tools.h"

void printCopyFile(int src, int dest) {
    if(dest == 1) { // dest = stdout
        printHalfHalf(src);
    } else {        // other dest

    }
}

int main( int argc, char *argv[] ) {
    if( argc < 3 ) {
        char *usage = "Usage: FileTwister <src> <dest>\n";
        if(write(1, usage, strlen(usage)) != strlen(usage)) {
            writeError("An error occurred while writing to stdout\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    /* Open input file */
    char *src  = argv[1];
    int fd_src = open(src, O_RDONLY);
    if(fd_src < -1) {
        perror("Could not open input file: ");
        return EXIT_FAILURE;
    }


    printCopyFile(fd_src, 1);


    //char *dest = argv[2];

    /* Close input file */
    if(close(fd_src)) {
        perror("Could not close input file: ");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}