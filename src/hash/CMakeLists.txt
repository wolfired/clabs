include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(
    adler32_test
    adler32_test.c
)
target_link_libraries(
    adler32_test
    cmocka
    clabs_static
)
add_test(test_adler32, adler32_test)


add_executable(
    crc32_test
    crc32_test.c
)
target_link_libraries(
    crc32_test
    cmocka
    clabs_static
)
add_test(test_crc32, crc32_test)
