if (NOT MSVC)
    include_directories(${CMOCKA_INCLUDE_DIR})

    add_executable(
        buf_test
        buf_test.c
    )
    target_link_libraries(
        buf_test
        cmocka
        clabs_static
    )

    add_test(test_buf, buf_test)
endif()
