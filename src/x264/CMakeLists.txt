find_library(
    LIB_X264
    x264
    ${X264_PATH}
)

include_directories(
    ${X264_PATH}
)

#
add_library(
    clabs_x264
    STATIC
    clabs_x264.h
    clabs_x264.c
)

#
add_executable(
    test_x264
    test_x264.c
)

target_link_libraries(
    test_x264
    clabs_x264
    ${LIB_X264}
)
