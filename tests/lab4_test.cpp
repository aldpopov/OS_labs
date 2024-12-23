#include <gtest/gtest.h>
#include <math.h>
#include "../LW4/src/libmath1.c"
#include "../LW4/src/libmath2.c"

// Тесты для библиотеки libmath1
TEST(LibMath1Test, SinIntegral) {
    //std::cout << SinIntegral_rectangle(1.5, 5.2, 0.1);
    EXPECT_NEAR(SinIntegral_rectangle(0.0, M_PI, 0.001), 2.0, 0.01);
    EXPECT_NEAR(SinIntegral_rectangle(0.0, M_PI / 2, 0.001), 1.0, 0.01);
}

TEST(LibMath1Test, Derivative) {
    //std::cout << Derivative_first(0.0, 0.001);
    EXPECT_NEAR(Derivative_first(0.0, 0.001), -sin(0.0), 0.001);
    EXPECT_NEAR(Derivative_first(M_PI / 2, 0.001), -sin(M_PI / 2), 0.001);
}

// Тесты для библиотеки libmath2
TEST(LibMath2Test, SinIntegral) {
    //std::cout << SinIntegral_trapezoid(0.0, M_PI, 0.001);
    EXPECT_NEAR(SinIntegral_trapezoid(0.0, M_PI, 0.001), 2.0, 0.01);
    EXPECT_NEAR(SinIntegral_trapezoid(0.0, M_PI / 2, 0.001), 1.0, 0.01);
}

TEST(LibMath2Test, Derivative) {
    //std::cout << Derivative_second(0.0, 0.001);
    EXPECT_NEAR(Derivative_second(0.0, 0.001), -sin(0.0), 0.001);
    EXPECT_NEAR(Derivative_second(M_PI / 2, 0.001), -sin(M_PI / 2), 0.001);
}