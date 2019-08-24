cmake_minimum_required(VERSION 3.10)

project(CLabs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(
    ./src
)

add_subdirectory(src)

if(${ENABLE_WASM} STREQUAL "true")
    add_subdirectory(src/wasm)
else()
    add_subdirectory(src/file)
    add_subdirectory(src/qjs)
    add_subdirectory(src/x264)
endif()
