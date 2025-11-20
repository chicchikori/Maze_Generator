file(GLOB_RECURSE cppfiles ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

set(DLL_NAME UnionFind)

add_library(${DLL_NAME} STATIC ${cppfiles})

target_include_directories(${DLL_NAME} PUBLIC ./header)

target_compile_features(${DLL_NAME} PRIVATE cxx_std_20)

