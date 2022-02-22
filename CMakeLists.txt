cmake_minimum_required(VERSION 3.16.3)

project(program1)
set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
set(CMAKE_C_FLAGS -pthread)
target_link_libraries(${program1} Threads::Threads)
add_executable(program1 main.c)
