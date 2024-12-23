#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <limits.h>


typedef float (*SinIntegralFunc)(float, float, float);
typedef float (*DerivativeFunc)(float, float);

int main() {
    void *handle;
    SinIntegralFunc SinIntegral;
    DerivativeFunc Derivative;
    char *error;
    float A, B, e, deltaX;
    int command;
    int scanf_result;


    handle = dlopen("build/LW4/liblibmath1.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral_rectangle");
    Derivative = (DerivativeFunc)dlsym(handle, "Derivative_first");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    while (1) {
        printf("Enter command (1 for SinIntegral, 2 for Derivative, 0 to switch, -1 to exit): ");

        scanf_result = scanf("%d", &command);
        if (scanf_result != 1) {
            printf("Invalid command input. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }


        if (command == -1) {
            break;
        } else if (command == 0) {
            dlclose(handle);
            handle = dlopen("build/LW4/liblibmath2.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                return 1;
            }
            SinIntegral = (SinIntegralFunc)dlsym(handle, "SinIntegral_trapezoid");
            Derivative = (DerivativeFunc)dlsym(handle, "Derivative_second");
            if ((error = dlerror()) != NULL) {
                fprintf(stderr, "%s\n", error);
                return 1;
            }
            printf("Switched to libmath2.so\n");
        } else if (command == 1) {
            printf("Enter A, B, e: ");
            scanf_result = scanf("%f %f %f", &A, &B, &e);
            if (scanf_result != 3) {
                printf("Invalid input for A, B, or e. Please enter three numbers.\n");
                while (getchar() != '\n');
                continue;
            }
            if (e <= 0 || B <= A) {
                printf("Error: e must be greater than zero and B must be greater than A.\n");
                continue;
            }
            printf("SinIntegral: %f\n", SinIntegral(A, B, e));
        } else if (command == 2) {
            printf("Enter A, deltaX: ");
            scanf_result = scanf("%f %f", &A, &deltaX);
            if (scanf_result != 2) {
                printf("Invalid input for A or deltaX. Please enter two numbers.\n");
                while (getchar() != '\n');
                continue;
            }
            if (deltaX <= 0) {
                printf("Error: deltaX must be greater than zero.\n");
                continue;
            }
            printf("Derivative: %f\n", Derivative(A, deltaX));
        } else {
            printf("Unknown command\n");
        }
    }

    dlclose(handle);
    return 0;
}
