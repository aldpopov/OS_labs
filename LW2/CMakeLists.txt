set(CMAKE_C_STANDARD 11)

add_executable(lab2 main.c include/lab2.h src/lab_2_utils.c)
target_include_directories(lab2 PRIVATE include)