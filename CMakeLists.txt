cmake_minimum_required(VERSION 3.0)
project(OpenCVClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(OpenCV REQUIRED)

set(PROJECT_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/headers)
set(PROJECT_NATIVE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/native)

file(GLOB_RECURSE PROJECT_HEADERS_FILES ${PROJECT_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE PROJECT_NATIVE_FILES ${PROJECT_NATIVE_DIR}/*.cpp)

include_directories(${PROJECT_HEADERS_DIR})

add_executable(OpenCVClient ${PROJECT_HEADERS_FILES} ${PROJECT_NATIVE_FILES})

target_link_libraries(OpenCVClient ${OpenCV_LIBS})
target_link_libraries(OpenCVClient pthread)
