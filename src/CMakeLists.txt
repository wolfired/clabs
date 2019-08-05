add_library(
    clabs
    STATIC
    clabs.h
    clabs.c
)

#
add_executable(
    test_trace
    test_trace.c
)

target_link_libraries(
    test_trace
    clabs
)
