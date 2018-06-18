#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "tools.h"

void writeError(const char* errorMsg) {
    const char *error = errorMsg;
    write(2, error, strlen(error));
}

off_t getFileSize(const int fd) {
    struct stat fileStat;
    if(fstat(fd,&fileStat) < 0) {
        return (off_t)-1;
    } else {
        return fileStat.st_size;
    }
}

void printHalfHalf(const int fd) {
    char *buffer;
    off_t size = getFileSize(fd);

    /* Check size*/
    if(size < (off_t) 0) {
        writeError("Could not get input file size\n");
        return;
    }

    /* Print second half */
    if (lseek(fd, size/2, SEEK_CUR) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
    if ( (buffer = malloc(size - size/2)) == NULL ) {
        writeError("printHalfHalf: Could not allocate memory");
        return;
    }
    if ( read(fd, buffer, size - size/2) < 0 ) {
        perror("printHalfHalf: ");
        return;
    }
    if(write(1, buffer, size - size/2) < 0) {
        perror("printHalfHalf: ");
        return;
    }
    free(buffer);

    /* Print first half */
    if (lseek(fd, 0, SEEK_SET) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
    if ( (buffer = malloc(size/2)) == NULL ) {
        writeError("printHalfHalf: Could not allocate memory");
        return;
    }
    if ( read(fd, buffer, size/2) < 0 ) {
        perror("printHalfHalf: ");
        return;
    }
    if(write(1, buffer, size/2) < 0) {
        perror("printHalfHalf: ");
        return;
    }
    free(buffer);

    /* Rewind */
    lseek(fd, 0, SEEK_SET);
}