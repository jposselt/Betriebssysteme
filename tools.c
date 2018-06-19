#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#include "tools.h"

#define BUFFER_SIZE 20
#define COPY_BYTES 10

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

/* Write bytes from a buffer */
int writeFromBuffer(int fd, char* buffer, size_t nBytes) {
    while(nBytes > 0) {
        ssize_t written = write(fd, buffer, nBytes);
        if (written < 0) {
            perror("writeFromBuffer: ");
            return -1;
        }
        nBytes -= written;
    }
    return 0;
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
        if ( writeFromBuffer(STDOUT, buffer, (size_t) nRead) < 0) {
            writeError("printHalfHalf: Could not write to stdout\n");
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
        if ( writeFromBuffer(STDOUT, buffer, (size_t) nRead) < 0) {
            writeError("printHalfHalf: Could not write to stdout\n");
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

    /* Rewind files */
    if (dest > STDERR) {
        lseek(dest, 0, SEEK_SET);
    }
    if (src > STDERR) {
        lseek(src, 0, SEEK_SET);
    }

}


void fileInsert(const int src, const int dest) {
    long int size = getFileSize(src);
    long int totalBytesToMove = MAX(size - COPY_BYTES, 0);
    long int insertPosition = MIN( MAX(size - 1, 0), COPY_BYTES);

    /* Get last COPY_BYTES characters from src */
    char insertBuffer[COPY_BYTES];
    if(lseek(src, MAX(size - COPY_BYTES -1,0), SEEK_SET) < 0) {
        perror("fileInsert: ");
        return;
    }
    ssize_t actualCopy = read(src, insertBuffer, (size_t) MIN(COPY_BYTES, size));
    if (actualCopy < 0) {
        perror("fileInsert: ");
        return;
    }

    /* Insert for files shorter than COPY_BYTES */
    if (totalBytesToMove == 0) {
        if (lseek(dest, insertPosition, SEEK_SET) < 0) {
            perror("fileInsert: ");
            return;
        }
        if (write(dest, insertBuffer, (size_t) actualCopy) < 0) {
            perror("fileInsert: ");
            return;
        }
    } else {
        /* Insert with moving of end bytes */
        char moveBuffer[BUFFER_SIZE];
        while (totalBytesToMove > 0) {
            /* Calculate and set the position from there to read */
            long int readPosition = insertPosition + totalBytesToMove - MIN(BUFFER_SIZE, totalBytesToMove);
            if (lseek(dest, readPosition, SEEK_SET) < 0) {
                writeError("fileInsert: Could not set destination read position\n");
                perror("fileInsert: ");
                return;
            }
            ssize_t movingBytes = read(dest, moveBuffer, (size_t) MIN(BUFFER_SIZE, totalBytesToMove));
            if( movingBytes < 0 ) {
                writeError("fileInsert: Could not read bytes for moving\n");
                perror("fileInsert: ");
                return;
            }

            /* Shift the bytes to their new position */
            long int writePosition = readPosition + COPY_BYTES;
            if (lseek(dest, writePosition, SEEK_SET) < 0) {
                writeError("fileInsert: Could not set destination write position\n");
                perror("fileInsert: ");
                return;
            }

            if ( writeFromBuffer(dest, moveBuffer, (size_t) movingBytes) < 0) {
                writeError("fileInsert: Could not write bytes for moving\n");
                return;
            }

            /* Update counter */
            totalBytesToMove -= movingBytes;
        }

        /* Insert new bytes */
        if (lseek(dest, insertPosition, SEEK_SET) < 0) {
            writeError("fileInsert: Could not set destination write position\n");
            perror("fileInsert: ");
            return;
        }
        if ( writeFromBuffer(dest, insertBuffer, (size_t) actualCopy) < 0) {
            writeError("fileInsert: Could not write bytes for inserting\n");
            return;
        }
    }

    /* Rewind files */
    if (dest > STDERR) {
        lseek(dest, 0, SEEK_SET);
    }
    if (src > STDERR) {
        lseek(src, 0, SEEK_SET);
    }
}
