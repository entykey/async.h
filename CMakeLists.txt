cmake_minimum_required(VERSION 3.0)
project(async_example C)

# Add executable
add_executable(async_example main.c)

# Include async.h header file
target_include_directories(async_example PRIVATE async)

# Set language to C for the entire project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
