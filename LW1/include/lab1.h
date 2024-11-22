#pragma once

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void CreateChildProcess(const char* filename, int pipefd[2]);
void ReadFromPipe(int pipefd[2], FILE* output);
void MainTestFunction(const char* filename, FILE* output);

