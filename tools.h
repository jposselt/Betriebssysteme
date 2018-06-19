#ifndef BETRIEBSSYSTEME_07_TOOLS_H
#define BETRIEBSSYSTEME_07_TOOLS_H

#define STDOUT 1
#define STDERR 2

void writeError(const char* errorMsg);

off_t getFileSize(const int fd);

void printHalfHalf(const int fd);

#endif //BETRIEBSSYSTEME_07_TOOLS_H
