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
        src/main/c++/native/opencv/OpenCVTool.hpp
        src/main/c++/native/Profiler.cpp
        src/main/c++/headers/Profiler.hpp
        src/main/c++/native/network/stream/StreamClient.cpp
        src/main/c++/headers/network/stream/StreamClient.hpp
        src/main/c++/native/network/stream/ImagePacket.cpp
        src/main/c++/headers/network/stream/ImagePacket.hpp
        src/main/c++/native/network/ServerAddr.cpp
        src/main/c++/headers/network/ServerAddr.hpp
        src/main/c++/native/network/properties/PropertiesClient.cpp
        src/main/c++/headers/network/properties/PropertiesClient.hpp
        src/main/c++/native/network/properties/TCPClient.cpp
        src/main/c++/headers/network/properties/TCPClient.hpp
        src/main/c++/native/network/exceptions/RuntimeException.cpp
        src/main/c++/headers/network/exceptions/RuntimeException.hpp
        src/main/c++/native/network/exceptions/IOException.cpp
        src/main/c++/headers/network/exceptions/IOException.hpp
        src/main/c++/native/opencv/FaceDetect.cpp
        src/main/c++/headers/opencv/FaceDetect.hpp
        src/main/c++/native/network/properties/protocol/out/AddPropertyPacket.cpp
        src/main/c++/headers/network/properties/protocol/out/AddPropertyPacket.hpp
        src/main/c++/native/network/properties/protocol/Protocol.cpp
        src/main/c++/headers/network/properties/protocol/Protocol.hpp
        src/main/c++/native/network/properties/protocol/OutPacket.cpp
        src/main/c++/headers/network/properties/protocol/OutPacket.hpp
        src/main/c++/native/network/properties/protocol/in/ChangePropertyPacket.cpp
        src/main/c++/headers/network/properties/protocol/in/ChangePropertyPacket.hpp
        src/main/c++/native/network/properties/protocol/InPacket.cpp
        src/main/c++/headers/network/properties/protocol/InPacket.hpp
        src/main/c++/native/network/properties/protocol/in/PingPacket.cpp
        src/main/c++/headers/network/properties/protocol/in/PingPacket.hpp
        src/main/c++/native/network/properties/protocol/out/PongPacket.cpp
        src/main/c++/headers/network/properties/protocol/out/PongPacket.hpp
        src/main/c++/native/network/properties/protocol/in/GetAllPropertiesPacket.cpp
        src/main/c++/headers/network/properties/protocol/in/GetAllPropertiesPacket.hpp
        src/main/c++/native/network/properties/protocol/in/GetPropertyPacket.cpp
        src/main/c++/headers/network/properties/protocol/in/GetPropertyPacket.hpp
        src/main/c++/native/network/properties/protocol/in/ResetPropertyPacket.cpp
        src/main/c++/headers/network/properties/protocol/in/ResetPropertyPacket.hpp
        src/main/c++/native/network/properties/protocol/out/RemovePropertyPacket.cpp
        src/main/c++/headers/network/properties/protocol/out/RemovePropertyPacket.hpp
        src/main/c++/native/network/properties/protocol/PacketType.cpp
        src/main/c++/headers/network/properties/protocol/PacketType.hpp
        src/main/c++/native/network/properties/protocol/Packet.cpp
        src/main/c++/headers/network/properties/protocol/Packet.hpp
        src/main/c++/native/network/properties/TCPPacketClient.cpp
        src/main/c++/headers/network/properties/TCPPacketClient.hpp
        src/main/c++/native/network/properties/protocol/out/AllPropertiesPacket.cpp
        src/main/c++/headers/network/properties/protocol/out/AllPropertiesPacket.hpp)

add_executable(OpenCVClient ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCVClient ${OpenCV_LIBS})
target_link_libraries(OpenCVClient pthread)
