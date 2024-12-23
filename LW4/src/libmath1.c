#include "libmath1.h"

float SinIntegral_rectangle(float A, float B, float e) {
    float sum = 0.0;
    for(float x = A; x < B; x += e) {
        sum += sin(x) * e;
    }
    return sum;
}

float Derivative_first(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}
