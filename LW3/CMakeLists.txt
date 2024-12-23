set(CMAKE_C_STANDARD 11)

add_executable(lab3 main.c src/utils.c src/parent.c)
target_include_directories(lab3 PRIVATE include)
add_executable(child src/child.c src/utils.c)
target_include_directories(child PRIVATE include)
add_dependencies(lab3 child)