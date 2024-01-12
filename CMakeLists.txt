cmake_minimum_required(VERSION 3.22)
project(MemoryManagement)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a list of source files in the src directory
file(GLOB SOURCE_FILES "src/*.cpp")

# Add an executable target
add_executable(MemoryManagement ${SOURCE_FILES})
