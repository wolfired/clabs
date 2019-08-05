cmake_minimum_required(VERSION 3.10)

project(CLabs)

find_library(
    LIB_QUICKJS
    quickjs
    /home/link/workspace_labs/quickjs-2019-07-09
)

# SHARED
# STATIC
add_library(
    clabs
    STATIC
    src/clabs.h
    src/clabs.c
    src/file.h
    src/file.c
)

target_include_directories(
    clabs
    PRIVATE /home/link/workspace_labs/quickjs-2019-07-09
)

target_link_libraries(
    clabs
    ${LIB_QUICKJS}
)

add_executable(
    main
    src/main.c
)

target_include_directories(
    main
    PRIVATE /home/link/workspace_labs/quickjs-2019-07-09
)

target_link_libraries(
    main
    dl
    m
    clabs
    ${LIB_QUICKJS}
)
