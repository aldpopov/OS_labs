set(CMAKE_C_STANDARD 11)

add_library(libmath1 SHARED src/libmath1.c)
target_include_directories(libmath1 PUBLIC include)
target_link_libraries(libmath1 m) # Добавлена математическая библиотека

add_library(libmath2 SHARED src/libmath2.c)
target_include_directories(libmath2 PUBLIC include)
target_link_libraries(libmath2 m) # Добавлена математическая библиотека

add_executable(lab4_static static.c)
target_link_libraries(lab4_static m libmath1 libmath2) # Убрано dl, добавлено m

add_executable(lab4_dynamic dynamic.c)
target_link_libraries(lab4_dynamic m libmath1 libmath2) # Убрано dl, добавлено m

