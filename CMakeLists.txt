cmake_minimum_required(VERSION 3.0)
project(OpenCVClient)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(
        src/main/c++/native
        src/main/c++/headers
)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES
        src/main/c++/headers/AppState.hpp
        src/main/c++/native/ClientApp.cpp
        src/main/c++/native/network/stream/ImagePacket.cpp
        src/main/c++/headers/network/stream/ImagePacket.hpp
        src/main/c++/native/opencv/OpenCVTool.hpp
        src/main/c++/native/Profiler.cpp
        src/main/c++/headers/Profiler.hpp
        src/main/c++/headers/network/properties/PropertiesClient.hpp
        src/main/c++/headers/network/ServerAddr.hpp
        src/main/c++/native/network/stream/StreamClient.cpp
        src/main/c++/headers/network/stream/StreamClient.hpp
        src/main/c++/native/network/ServerAddr.cpp
        src/main/c++/native/network/properties/PropertiesClient.cpp
        )

add_executable(OpenCVClient ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCVClient ${OpenCV_LIBS})
target_link_libraries(OpenCVClient pthread)
