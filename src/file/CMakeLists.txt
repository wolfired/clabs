add_library(
    clabs_file
    STATIC
    file.h
    file.c
)

#
add_executable(
    test_file
    test_file.c
)

target_link_libraries(
    test_file
    clabs_file
)
