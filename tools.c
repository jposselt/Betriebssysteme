#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "tools.h"

#define BUFFER_SIZE 2

void writeError(const char* errorMsg) {
    const char *error = errorMsg;
    write(STDERR, error, strlen(error));
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
    char buffer[BUFFER_SIZE];
    long int count;
    off_t size = getFileSize(fd);

    /* Check size */
    if(size < (off_t) 0) {
        writeError("Could not get input file size\n");
        return;
    }

    /* Print second half */
    if (lseek(fd, size/2, SEEK_CUR) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
    count = size - size/2;
    while (count > 0) {
        ssize_t nRead = read(fd, buffer, BUFFER_SIZE);
        if (nRead < 0) {
            perror("printHalfHalf: ");
            return;
        }
        if (write(1, buffer, (size_t)nRead) < 0) {
            perror("printHalfHalf: ");
            return;
        }
        count -= nRead;
    }

    /* Print first half */
    if (lseek(fd, 0, SEEK_SET) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
    count = size/2;
    while (count > 0) {
        ssize_t nRead = read(fd, buffer, BUFFER_SIZE);
        if (nRead < 0) {
            perror("printHalfHalf: ");
            return;
        }
        if (write(1, buffer, (size_t)nRead) < 0) {
            perror("printHalfHalf: ");
            return;
        }
        count -= nRead;
    }

    /* Rewind */
    if (lseek(fd, 0, SEEK_SET) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
}