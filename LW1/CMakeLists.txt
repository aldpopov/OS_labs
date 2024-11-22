set(CMAKE_C_STANDARD 11)

# add_library(utils include/lab1.h src/lab_1_utils.c)
# target_include_directories(utils PRIVATE include)
add_executable(lab1 main.c include/lab1.h src/lab_1_utils.c)
add_executable(divergent src/divergent.c include/lab1.h)
target_include_directories(lab1 PRIVATE include)
target_include_directories(divergent PRIVATE include)
# target_link_libraries(divergent utils)



# target_link_libraries(lab1 utils)