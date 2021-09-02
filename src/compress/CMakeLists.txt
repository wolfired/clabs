include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(
    flate_test
    flate_test.c
)
target_link_libraries(
    flate_test
    cmocka
    clabs_static
)

add_test(test_flate, flate_test)

add_executable(
    zlib_test
    zlib_test.c
)
target_link_libraries(
    zlib_test
    cmocka
    clabs_static
)

add_test(test_zlib, zlib_test)
