cmake_minimum_required(VERSION 2.8.4)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

set(SOURCE_FILES main.cpp Network.cpp Network.h User.cpp User.h Clash.cpp Clash.h)
add_executable(test ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(test pthread)
