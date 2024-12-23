set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

set(CONTROL_SRC
    ./main.c
    src/manage_node.c
    src/message.c
    src/tree.c
    src/upcoming_operations.c
)

set(COMP_SRC
    src/calc_node.c
    src/comp_utils.c
    src/message.c
    src/tree.c
    src/manage_node.c
    src/upcoming_operations.c
)

add_executable(manage_node ${CONTROL_SRC})
target_link_libraries(manage_node ${ZMQ_LIBRARIES})
add_executable(calc_node ${COMP_SRC})
target_link_libraries(calc_node ${ZMQ_LIBRARIES})