cmake_minimum_required(VERSION 3.10)

project(SoundProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/source/*.cpp")

add_executable(SoundProcessor ${SOURCES})

file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/headers/*.h")
set_source_files_properties(${HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)

include_directories(${CMAKE_SOURCE_DIR}/headers)