#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void CreateChildProcess(const char* filename, int pipefd[2]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Ошибка при создании процесса");
        exit(1);
    }

    if (pid == 0) { // Дочерний процесс
        char pipeFdStr[12]; // Buffer to hold pipe file descriptor as string
        snprintf(pipeFdStr, sizeof(pipeFdStr), "%d", pipefd[1]);

        char* args[] = {
            "/workspaces/OS_labs/build/LW1/divergent", 
            (char*)filename, 
            pipeFdStr, 
            NULL
        };

        if (execvp(args[0], args) == -1) {
            perror("Ошибка при запуске дочерней программы");
            exit(1);
        }

        _exit(0);
    }
}

void ReadFromPipe(int pipefd[2], FILE* output) {
    close(pipefd[1]);

    // чтение данных из pipe и вывод их на экран
    char buffer[1024];
    ssize_t n;
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, n, output); // Write to the output file stream
        fwrite(buffer, 1, n, stdout);  // Write to standard output
    }

    close(pipefd[0]);
}

void MainTestFunction(const char* filename, FILE* output) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("Ошибка при создании pipe");
        exit(1);
    }

    CreateChildProcess(filename, pipefd);

    ReadFromPipe(pipefd, output);

    wait(NULL);
}