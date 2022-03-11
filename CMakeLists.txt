cmake_minimum_required (VERSION 3.8)

project(
    diskspeedtest
    VERSION 0.1
    DESCRIPTION "A simple disk speed test"
    LANGUAGES CXX
)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(diskspeedtest ${SOURCES})

