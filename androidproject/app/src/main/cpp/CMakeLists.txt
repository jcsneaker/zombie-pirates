cmake_minimum_required(VERSION 3.4.1)
# set targetPlatform, will be passed in from gradle when this sample is completed
# openGL Supportability

#   [18, 24)         ES2 & ES3
#                    If app is built to only support API-18 or later,
#                    set minimum api level to 18 is good enough, NDK supprts ES3
#                    with the right header and lib files. No need to use ES3 dynamic
#                    detection.
#   [24, infinite)   ES2 & ES3 & Vulkan

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

file(GLOB
    RAMSES_ANDROIDINTERFACE_FILES_SOURCE
    *.cpp)

add_library(zombiepirates_android SHARED
            ${RAMSES_ANDROIDINTERFACE_FILES_SOURCE})

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


