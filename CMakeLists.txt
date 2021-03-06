#  -------------------------------------------------------------------------
#  Copyright (C) 2019 BMW Car IT GmbH
#  All rights reserved.
#  -------------------------------------------------------------------------
#  This document contains proprietary information belonging to BMW Car IT.
#  Passing on and copying of this document, use and communication of its
#  contents is not permitted without prior written authorization.
#  -------------------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

project (ZombiePiratesGame)


set (ZombiePiratesGame_VERSION_MAJOR 0)
set (ZombiePiratesGame_VERSION_MINOR 1)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(external)

# TODO after first version is done, refactor project structure
file(GLOB source_files
    PirateGame/src/*.cpp
    PirateGame/include/*.h
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(RND_PLATFORM platform-windows-wgl-4-2-core)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(RND_PLATFORM platform-x11-egl-es-3-0)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(RND_PLATFORM platform-android-egl-es-3-0)
endif()

set(ramses_dependencies
ramses-framework-api
ramses-framework
	ramses-client-api
	ramses-client
	ramses-renderer-api
    ramses-renderer-lib
	${RND_PLATFORM}


  )

IF (${CMAKE_SYSTEM_NAME} MATCHES "Android")
add_library(ZombiePiratesGame STATIC
            ${source_files})
ELSE()
add_executable(ZombiePiratesGame ${source_files})
ENDIF()

target_link_libraries(ZombiePiratesGame   ${ramses_dependencies} )
target_include_directories(ZombiePiratesGame PUBLIC PirateGame/include)

# TODO check if this is the right place
add_definitions(-DRAMSES_LINK_STATIC)


# Collect PTX files
file(GLOB_RECURSE ASSETS
	LIST_DIRECTORIES FALSE
	CONFIGURE_DEPENDS
	${PROJECT_SOURCE_DIR}/PirateGame/res/*
)

foreach(asset ${ASSETS})
  file(RELATIVE_PATH relativePath ${PROJECT_SOURCE_DIR}/PirateGame ${asset})
  configure_file(PirateGame/${relativePath} ${CMAKE_CURRENT_BINARY_DIR}/${relativePath} COPYONLY)
endforeach()
