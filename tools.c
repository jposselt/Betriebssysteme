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
    long int size = getFileSize(fd);

    /* Check size */
    if(size < 0) {
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
        if (write(STDOUT, buffer, (size_t)nRead) < 0) {
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
        if (write(STDOUT, buffer, (size_t)nRead) < 0) {
            perror("printHalfHalf: ");
            return;
        }
        count -= nRead;
    }

    if (write(STDOUT, "\n", 1) < 0 ) {
        perror("printHalfHalf: ");
        return;
    }

    /* Rewind */
    if (lseek(fd, 0, SEEK_SET) < (off_t) 0) {
        perror("printHalfHalf: ");
        return;
    }
}

void printFile(const int src, const int dest) {
    char buffer[BUFFER_SIZE];
    long int count = getFileSize(src);

    /* Check size */
    if(count < 0) {
        writeError("Could not get output file size\n");
        return;
    }

    while (count > 0) {
        ssize_t nRead = read(src, buffer, BUFFER_SIZE);
        if (nRead < 0) {
            perror("printFile: ");
            return;
        }
        if (write(dest, buffer, (size_t)nRead) < 0) {
            perror("printFile: ");
            return;
        }
        count -= nRead;
    }

    /* Rewind file */
    if(dest > STDERR) {
        lseek(dest, 0, SEEK_SET);
    }
}
