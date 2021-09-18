add_subdirectory(bufio)
add_subdirectory(cg)
add_subdirectory(compress)
add_subdirectory(container)
add_subdirectory(hash)
add_subdirectory(image)
add_subdirectory(math)

set(
    INCS
    bufio/buf.h
    cg/line.h
    cg/triangle.h
    compress/flate.h
    compress/zlib.h
    container/list.h
    container/list_singly_linked.h
    container/list_doubly_linked.h
    gc/mark_sweep.h
    hash/adler32.h
    hash/crc32.h
    image/png.h
    math/linear_algebra.h
)
set(
    SRCS
    bufio/buf.c
    cg/line.c
    cg/triangle.c
    compress/flate.c
    compress/zlib.c
    container/list_singly_linked.c
    container/list_doubly_linked.c
    gc/mark_sweep.c
    hash/adler32.c
    hash/crc32.c
    image/png.c
    math/linear_algebra.c
)

add_library(clabs_static STATIC ${SRCS})
target_include_directories(clabs_static PUBLIC .)
set_target_properties(clabs_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(clabs_shared SHARED ${SRCS})
target_include_directories(clabs_shared PUBLIC .)
set_target_properties(clabs_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(clabs_shared PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

install(TARGETS clabs_static clabs_shared LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${INCS} DESTINATION include/${PROJECT_NAME})

