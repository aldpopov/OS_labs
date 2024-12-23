#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libmath1.h"
#include "libmath2.h"

int main() {
    float A, B, e, deltaX;
    int command;
    int scanf_result;


    while (1) {
        printf("Enter command (1 for SinIntegral, 2 for Derivative, 0 to exit): ");
        scanf_result = scanf("%d", &command);

        if (scanf_result != 1) {
            printf("Invalid command input. Please enter an integer.\n");
            while (getchar() != '\n');
            continue;
        }


        if (command == 0) {
            break;
        } else if (command == 1) {
            printf("Enter A, B, e: ");
            scanf_result = scanf("%f %f %f", &A, &B, &e);
            if (scanf_result != 3) {
                printf("Invalid input for A, B, or e. Please enter three numbers.\n");
                while (getchar() != '\n');
                continue;
            }
            if (e <=0 || B <= A) {
                printf("Error: e must be greater than zero and B must be greater than A.\n");
                continue;
            }
            printf("SinIntegral_rectangle: %f\n", SinIntegral_rectangle(A, B, e));
            printf("SinIntegral_trapezoid: %f\n", SinIntegral_trapezoid(A, B, e));
        } else if (command == 2) {
            printf("Enter A, deltaX: ");
            scanf_result = scanf("%f %f", &A, &deltaX);
            if (scanf_result != 2) {
                printf("Invalid input for A or deltaX. Please enter two numbers.\n");
                while (getchar() != '\n');
                continue;
            }
            if (deltaX <=0) {
                printf("Error: deltaX must be greater than zero.\n");
                continue;
            }

            printf("Derivative_first: %f\n", Derivative_first(A, deltaX));
            printf("Derivative_second: %f\n", Derivative_second(A, deltaX));
        } else {
            printf("Unknown command\n");
        }
    }

    return 0;
}
