cmake_minimum_required(VERSION 3.10)
project(mai-os C CXX)

enable_testing()
add_subdirectory(LW1)
add_subdirectory(tests)

add_custom_target(run
    DEPENDS lab1
    COMMAND ${CMAKE_COMMAND} -E echo "Запуск приложения"
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR}/LW1
    COMMAND ${CMAKE_COMMAND} -E env PATH="${CMAKE_BINARY_DIR}/LW1:${PATH}" ./lab1
    COMMENT "Запуск приложения"
)
