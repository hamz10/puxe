cmake_minimum_required(VERSION 3.15)
project(gridray)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-std=c++20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(gridray src/main.cpp
        src/entities.cpp
        src/control.cpp
        src/grid.cpp
        include/gui.h
        src/gui.cpp
        include/UDP_server.h
        src/UDP_server.cpp)

target_include_directories(gridray PRIVATE ${raylib_INCLUDE_DIRS})

target_link_libraries(gridray PRIVATE ${raylib_LIBRARIES} glfw)
