cmake_minimum_required(VERSION 3.10)

project(lava-engine)

# set the output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# set compilation mode
set(CMAKE_BUILD_TYPE Debug)

# generating compilation database for libclang for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# vulkan library
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIR})

# GLFW library
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

add_subdirectory(src)
