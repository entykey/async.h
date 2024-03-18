cmake_minimum_required(VERSION 3.0)
project(async)

# Create a dummy target if no source files are found
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/async.c")
    add_library(async INTERFACE)
else()
    message(FATAL_ERROR "No source files found for async library")
endif()

# Set include directory
target_include_directories(async INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
