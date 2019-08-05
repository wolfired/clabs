find_library(
    LIB_QUICKJS
    quickjs
    /home/link/workspace_labs/quickjs-2019-07-09
)

include_directories(
    /home/link/workspace_labs/quickjs-2019-07-09
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
