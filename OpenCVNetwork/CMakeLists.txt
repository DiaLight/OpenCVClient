cmake_minimum_required(VERSION 2.6)
project(OpenCVNetwork)

message(STATUS "OpenCVNetwork PROJECT_NAME: " ${PROJECT_NAME})
set(PROJECT_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/headers)
set(PROJECT_NATIVE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/native)
file(GLOB_RECURSE PROJECT_HEADERS_FILES ${PROJECT_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE PROJECT_NATIVE_FILES ${PROJECT_NATIVE_DIR}/*.cpp)

include_directories(${PROJECT_HEADERS_DIR})
add_library(${PROJECT_NAME} SHARED ${PROJECT_HEADERS_FILES} ${PROJECT_NATIVE_FILES})

include_directories(${Properties_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Properties)

#share variables through project name
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_HEADERS_DIR}
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)