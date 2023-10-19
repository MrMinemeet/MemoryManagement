cmake_minimum_required(VERSION 3.22)
project(SystemSoftware_MemoryManagement)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add an executable target
add_executable(SystemSoftware_MemoryManagement src/main.cpp)
