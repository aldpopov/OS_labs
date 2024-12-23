#include "utils.h"
#include "fcntl.h"
#include <sys/mman.h>
#include <unistd.h>


void TrimString(char *str) {
    size_t start = 0, end = strlen(str) - 1;

    while (isspace(str[start])) {
        start++;
    }

    while (end > start && isspace(str[end])) {
        end--;
    }

    if (start > 0 || end < (strlen(str) - 1)) {
        memmove(str, str + start, end - start + 1);
        str[end - start + 1] = '\0';
    }
}


int CreateProcess(void) {
    pid_t pid = fork();
    if (-1 == pid) {
        perror("fork");
        exit(-1);
    }
    return pid;
}


int OpenSHM(char *filename, int size) {
    int fd = shm_open(filename, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, size);
    return fd;
}

int OpenFile(char *filename) {
    TrimString(filename);
    int fd = open(filename, O_RDONLY);
    return fd;
}