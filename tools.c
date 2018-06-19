#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "tools.h"

#define BUFFER_SIZE 2
#define NCOPY 10

/* Write an error message to stderr */
void writeError(const char* errorMsg) {
    const char *error = errorMsg;
    write(STDERR, error, strlen(error));
}

/* Get the size of a file in bytes */
off_t getFileSize(const int fd) {
    struct stat fileStat;
    if(fstat(fd,&fileStat) < 0) {
        return (off_t)-1;
    } else {
        return fileStat.st_size;
    }
}

/* Print second then first half of file to stdout */
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
        ssize_t nRead = read(fd, buffer, (size_t) MIN(BUFFER_SIZE, count));
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
        ssize_t nRead = read(fd, buffer, (size_t) MIN(BUFFER_SIZE, count));
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

/* Print file to another file descriptor */
void printFile(const int src, const int dest) {
    char buffer[BUFFER_SIZE];
    long int count = getFileSize(src);

    /* Check size */
    if(count < 0) {
        writeError("Could not get output file size\n");
        return;
    }

    /* Read file pice by pice and write pices to stdout */
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


void fileInsert(const int src, const int dest) {
    long int insertPosition;
    long int size = getFileSize(src);
    long int bytesToMove = size - NCOPY;

    char insertBuffer[NCOPY];
    if (read(src, insertBuffer, NCOPY) < 0) {
        perror("fileInsert: ");
        return;
    }

//    if (size < (NCOPY + 1)) {
//
//    } else {
//        insertPosition = NCOPY + 1;
//        char moveBuffer[BUFFER_SIZE];
//    }
}
