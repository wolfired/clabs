if (NOT MSVC)
    include_directories(${CMOCKA_INCLUDE_DIR})

    add_executable(
        png_test
        png_test.c
    )
    target_link_libraries(
        png_test
        cmocka
        clabs_static
    )

    add_test(test_png, png_test)
endif()
