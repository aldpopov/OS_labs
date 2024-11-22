#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab1.h"

int main() {
    char name[256]; // Buffer to hold the filename input
    printf("Enter file's name:\n");
    
    // Read the filename from standard input
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '0';
        }
    } else {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    // Call the function that processes the file
    MainTestFunction(name, stdout); // Assuming MainTestFunction can take stdout as output

    return EXIT_SUCCESS; 
}
