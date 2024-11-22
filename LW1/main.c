#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab1.h"

int main() {
    char name[256];
    printf("Enter file's name:\n");
    
    if (fgets(name, sizeof(name), stdin) != NULL) {
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    MainTestFunction(name, stdout);

    return EXIT_SUCCESS; 
}
