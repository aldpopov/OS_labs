include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


find_package(PkgConfig REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)
set(CMAKE_CXX_STANDARD 20)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

set(CONTROL_SRC
    ../LW5-7/mock_main.c
    ../LW5-7/src/manage_node.c
    ../LW5-7/src/message.c
    ../LW5-7/src/tree.c
    ../LW5-7/src/upcoming_operations.c
)

set(COMP_SRC
    ../LW5-7/src/comp_utils.c
    ../LW5-7/src/message.c
)

add_executable(LW1_test lab1_test.cpp ../LW1/src/lab_1_utils.c ../LW1/include/lab1.h)
target_link_libraries(LW1_test PRIVATE GTest::GTest)
target_include_directories(LW1_test PRIVATE ../LW1/include)

add_executable(LW2_test lab2_test.cpp ../LW2/src/lab_2_utils.c ../LW2/include/lab2.h)
target_link_libraries(LW2_test PRIVATE GTest::GTest)
target_include_directories(LW2_test PRIVATE ../LW2/include)

add_executable(LW3_test lab3_test.cpp ../LW3/src/parent.c ../LW3/src/utils.c)
target_link_libraries(LW3_test PRIVATE GTest::GTest)
target_include_directories(LW3_test PRIVATE ../LW3/include)

add_executable(LW4_test lab4_test.cpp ../LW4/src/libmath1.c ../LW4/src/libmath2.c)
target_link_libraries(LW4_test PRIVATE GTest::GTest libmath1 libmath2)
target_include_directories(LW4_test PRIVATE ../LW4/include)

add_executable(LW5-7_test lab5-7_test.cpp ${CONTROL_SRC})
target_link_libraries(LW5-7_test PRIVATE GTest::GTest ${ZeroMQ_LIBRARIES})
target_include_directories(LW5-7_test PRIVATE ../LW5-7/include ${ZeroMQ_INCLUDE_DIRS})

add_executable(CP8_test cp8_test.cpp ../CP8/src/cp8_utils.cpp)
target_link_libraries(CP8_test PRIVATE GTest::GTest)
target_include_directories(CP8_test PRIVATE ../CP8/include yaml-cpp)

enable_testing()
add_test(NAME LW1_test COMMAND LW1_test)
add_test(NAME LW2_test COMMAND LW2_test)
add_test(NAME LW3_test COMMAND LW3_test)
add_test(NAME LW4_test COMMAND LW4_test)
add_test(NAME LW5-7_test COMMAND LW5-7_test)
add_test(NAME CP8_test COMMAND CP8_test)