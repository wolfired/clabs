if (NOT MSVC)
    include_directories(${CMOCKA_INCLUDE_DIR})

    add_executable(
        list_singly_linked_test
        list_singly_linked_test.c
    )
    target_link_libraries(
        list_singly_linked_test
        cmocka
        clabs_static
    )
    add_test(test_list_singly_linked, list_singly_linked_test)

    add_executable(
        list_doubly_linked_test
        list_doubly_linked_test.c
    )
    target_link_libraries(
        list_doubly_linked_test
        cmocka
        clabs_static
    )
    add_test(test_list_doubly_linked, list_doubly_linked_test)
endif()
