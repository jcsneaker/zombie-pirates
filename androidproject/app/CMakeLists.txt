cmake_minimum_required(VERSION 3.10)

MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(../../ build-ramsessdk)
add_subdirectory(src/main/cpp)
