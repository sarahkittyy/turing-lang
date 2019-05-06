cmake_minimum_required(VERSION 3.13)
project(T-LANG)

option(BUILD_DEBUG "Build the debug binaries" off)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall)
if(BUILD_DEBUG)
	add_compile_options(-g)
endif()

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(tlang ${sources})

target_include_directories(tlang PUBLIC "include")
