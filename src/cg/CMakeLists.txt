# include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(
    line_test
    line_test.c
)
target_link_libraries(
    line_test
    # cmocka
    clabs_static
)

# add_test(test_buf, line_test)
