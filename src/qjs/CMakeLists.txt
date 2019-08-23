find_library(
    LIB_QUICKJS
    quickjs
    ${QJS_PATH}
)

include_directories(
    ${QJS_PATH}
)

#
add_library(
    clabs_qjs
    STATIC
    qjs.h
    qjs.c
)

#
add_executable(
    test_qjs
    test_qjs.c
)

target_link_libraries(
    test_qjs
    dl
    m
    clabs_qjs
    ${LIB_QUICKJS}
)
