include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(
    buf_test
    buf_test.c
    buf.c
)
target_link_libraries(
    buf_test
    cmocka
)
# target_include_directories(
#     buf_test
#     PRIVATE
#     ..
# )

add_test(test_buf, buf_test)
