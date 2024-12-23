#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

#define SHARED_MEMORY_SIZE 4096
#define SEM_NAME "/my_semaphore"
#define SHARED_MEMORY_NAME "/my_shared_memory"

extern void parent_process(sem_t *sem, char *shared_memory);
extern void child_process(sem_t *sem, char *shared_memory);