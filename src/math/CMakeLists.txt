# include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(
    linear_algebra_test
    linear_algebra_test.c
)
target_link_libraries(
    linear_algebra_test
    # cmocka
    clabs_static
)

# add_test(test_linear_algebra, linear_algebra_test)
