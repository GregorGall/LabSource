cmake_minimum_required(VERSION 3.0)
project(LabSourceLib)

set(CMAKE_BINARY_DIR ./build)

add_subdirectory(./DMath)
aux_source_directory(./source SOURCE)
add_library(LabSource STATIC ${SOURCE})
target_include_directories(LabSource PUBLIC ./include)
target_link_libraries(LabSource DMath)

