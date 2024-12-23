#include "lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

void ProcessData(int writeFd) {
    float num, sum = 0;
    char buffer[1024];
    char *token;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *line = strtok(buffer, "\n");
        while (line != NULL) {
            sum = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                num = atof(token);
                sum += num;
                token = strtok(NULL, " ");
            }
            char resultStr[1024];
            snprintf(resultStr, sizeof(resultStr), "Sum: %.2f\n", sum);
            ssize_t bytesWritten = write(writeFd, resultStr, strlen(resultStr));
            if (bytesWritten == -1) {
                fprintf(stderr, "Write error: %s\n", strerror(errno));
                exit(1);
            } else if (bytesWritten < strlen(resultStr)) {
                fprintf(stderr, "Warning: written only %zd bytes from %zu\n", bytesWritten, strlen(resultStr));
            }
            line = strtok(NULL, "\n");
        }
    }
    /*while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        token = strtok(buffer, " \n");
        while (token != NULL) {
            num = atof(token);
            sum += num;
            token = strtok(NULL, " \n");
        }
    }

    char resultStr[1024];
    snprintf(resultStr, sizeof(resultStr), "Sum: %.2f\n", sum);

    ssize_t bytesWritten = write(writeFd, resultStr, strlen(resultStr));

    if (bytesWritten == -1) {
        fprintf(stderr, "Write error: %s\n", strerror(errno));
        exit(1);
    } else if (bytesWritten < strlen(resultStr)) {
        fprintf(stderr, "Warning: written only %zd bytes from %zu\n", bytesWritten, strlen(resultStr));
    }*/

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

    if (*endptr != '\0' || writeFdLong < INT_MIN || writeFdLong > INT_MAX) {
        fprintf(stderr,"Invalid writeFd\n");
        return 1;
    }

    writeFd = (int) writeFdLong;
    ProcessData(writeFd);

    return 0;
}
