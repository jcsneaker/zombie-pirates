cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

file(GLOB
    SOURCES
    *.cpp)

add_library(zombiepirates_android SHARED
            ${SOURCES})

# Include libraries needed for gles3jni lib
target_link_libraries(zombiepirates_android
        ZombiePiratesGame
        ramses-renderer-lib
            GLESv3
            android
            EGL
            log
            m
        )


