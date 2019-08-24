add_library(
    clabs
    STATIC
    clabs.h
    clabs.c
)

#
add_executable(
    test_clabs
    test_clabs.c
)

target_link_libraries(
    test_clabs
    clabs
)
