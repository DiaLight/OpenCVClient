cmake_minimum_required(VERSION 3.0)
project(OpenCVClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(PROJECT_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/headers)
set(PROJECT_NATIVE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/main/c++/native)
file(GLOB_RECURSE PROJECT_HEADERS_FILES ${PROJECT_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE PROJECT_NATIVE_FILES ${PROJECT_NATIVE_DIR}/*.cpp)

# build executable
include_directories(${PROJECT_HEADERS_DIR})
add_executable(${PROJECT_NAME} ${PROJECT_HEADERS_FILES} ${PROJECT_NATIVE_FILES})

# build and link subprojects
add_subdirectory(OpenCVNetwork)
include_directories(${OpenCVNetwork_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} OpenCVNetwork)

# link dependencies
find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} pthread)


#MESSAGE( STATUS "OpenCVNetwork_SOURCE_DIR: " ${OpenCVNetwork_SOURCE_DIR} )