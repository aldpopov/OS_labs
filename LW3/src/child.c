#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "utils.h"
#include <sys/mman.h>
#include "semaphore.h"


int main() {
    const int BUFFER_SIZE = 1024 * 10;
    char buffer[BUFFER_SIZE];

    sem_t *semaphore_write = sem_open("/semaphore_write", 0);
    sem_t *semaphore_read = sem_open("/semaphore_read", 0);

    char *ptr = (char*) mmap(0, BUFFER_SIZE, PROT_WRITE, MAP_SHARED, STDOUT_FILENO, 0);
    char *token;
    float num;
    float sum;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *line = strtok(buffer, "\n");
        while (line != NULL) {
            sem_wait(semaphore_write);
            sum = 0;
            token = strtok(line, " ");
            while (token != NULL) {
                num = atof(token);
                sum += num;
                token = strtok(NULL, " ");
            }
            sprintf(ptr, "%.2f", sum);
            sem_post(semaphore_read);
            line = strtok(NULL, "\n");
        }
    }
    sem_wait(semaphore_write);
    sprintf(ptr, "%s", "stop");
    sem_post(semaphore_read);
    munmap(ptr, BUFFER_SIZE);
    sem_close(semaphore_read);
    sem_close(semaphore_write);
    exit(EXIT_SUCCESS);

}