#ifndef BETRIEBSSYSTEME_07_TOOLS_H
#define BETRIEBSSYSTEME_07_TOOLS_H

#define STDOUT 1
#define STDERR 2

#define MIN(a,b) (((a)<(b))?(a):(b))

void writeError(const char* errorMsg);
off_t getFileSize(const int fd);
void printHalfHalf(const int fd);
void printFile(const int src, const int dest);
void fileInsert(const int src, const int dest);

#endif //BETRIEBSSYSTEME_07_TOOLS_H
