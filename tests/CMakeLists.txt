include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 20)

add_executable(LW1_test lab1_test.cpp ../LW1/src/lab_1_utils.c ../LW1/include/lab1.h)
target_link_libraries(LW1_test PRIVATE GTest::GTest)
target_include_directories(LW1_test PRIVATE ../LW1/include)


enable_testing()
add_test(NAME LW1_test COMMAND LW1_test)