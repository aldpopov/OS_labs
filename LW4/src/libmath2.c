#include "libmath2.h"

float SinIntegral_trapezoid(float A, float B, float e) {
    float sum = 0.0;
    for(float x = A; x < B; x += e) {
        sum += (sin(x) + sin(x + e)) / 2 * e;
    }
    return sum;
}

float Derivative_second(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A - deltaX)) / (2 * deltaX);
}