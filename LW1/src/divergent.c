#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>


void ProcessData(int writeFd) {
    int num, sum = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
      num = atoi(buffer);
      sum += num;
    }
    
    char resultStr[1024]; //Ensure sufficient buffer size
    snprintf(resultStr, sizeof(resultStr), "Sum: %d\n", sum);

    ssize_t bytesWritten = write(writeFd, resultStr, strlen(resultStr));

    if (bytesWritten == -1) {
        fprintf(stderr, "Write error: %s\n", strerror(errno));
        exit(1); //Exit on error in C
    } else if (bytesWritten < strlen(resultStr)) {
        fprintf(stderr, "Warning: written only %zd bytes from %zu\n", bytesWritten, strlen(resultStr));
    }

    close(writeFd);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <writeFd>\n", argv[0]);
        return 1;
    }

    int file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror("Opening error");
        return 1;
    }

    if (dup2(file, STDIN_FILENO) == -1) {
        perror("dup2 error");
        close(file);
        return 1;
    }
    close(file);

    int writeFd;
    char *endptr;
    long int writeFdLong = strtol(argv[2], &endptr, 10);

    //Error handling for strtol
    if (*endptr != '\0' || writeFdLong < INT_MIN || writeFdLong > INT_MAX) {
        fprintf(stderr,"Invalid writeFd\n");
        return 1;
    }

    writeFd = (int) writeFdLong;
    ProcessData(writeFd);

    return 0;
}
