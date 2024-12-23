find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

# Укажите путь к заголовочным файлам и библиотекам
include_directories(${YAML_CPP_INCLUDE_DIRS})
link_directories(${YAML_CPP_LIBRARY_DIRS})

# Добавление библиотеки tools
add_library(cp_tools src/tools.cpp)
target_include_directories(cp_tools PRIVATE include)
target_link_libraries(cp_tools PRIVATE ${YAML_CPP_LIBRARIES})

# Добавление исполняемого файла
add_executable(cp main.cpp)
target_include_directories(cp PRIVATE include)
target_link_libraries(cp PRIVATE cp_tools ${YAML_CPP_LIBRARIES})