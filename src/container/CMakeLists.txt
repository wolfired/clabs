add_executable(
    list_singly_linked_test
    list_singly_linked_test.c
    list_singly_linked.c
)
target_link_libraries(
    list_singly_linked_test
    cmocka
)
# target_include_directories(
#     list_singly_linked_test
#     PRIVATE
#     ..
# )

add_executable(
    list_doubly_linked_test
    list_doubly_linked_test.c
    list_doubly_linked.c
)
target_link_libraries(
    list_doubly_linked_test
    cmocka
)
# target_include_directories(
#     list_doubly_linked_test
#     PRIVATE
#     ..
# )
