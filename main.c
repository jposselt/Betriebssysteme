#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h> /* fuer Kontrollfluss */
#include <unistd.h>

int main( int argc, char *argv[] ) {
    if( argc < 3 ) {
        char *usage = "Usage: FileTwister <src> <dest>\n";
        if(write(1, usage, strlen(usage)) != strlen(usage)) {
            char *error = "An error occurred while writing to stdout";
            write(2, error, strlen(error));
        }
        
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}