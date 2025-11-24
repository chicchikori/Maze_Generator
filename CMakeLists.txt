cmake_minimum_required(VERSION 3.10)

project(UnionFind)

file(GLOB_RECURSE cppfiles ${CMAKE_CURRENT_SOURCE_DIR}/maze/src/*.cpp )

set(DLL_NAME UnionFind)

add_library(${DLL_NAME} SHARED ${cppfiles})

target_include_directories(${DLL_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/maze/header)

target_compile_features(${DLL_NAME} PRIVATE cxx_std_20)

