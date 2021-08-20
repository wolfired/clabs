add_subdirectory(container)

set(
    CONTAINER_INC
    container/list.h
    container/list_singly_linked.h
)
set(
    CONTAINER_SRC
    container/list_singly_linked.c
)

add_library(clabs_static STATIC ${CONTAINER_SRC})
target_include_directories(clabs_static PUBLIC . ./container)
set_target_properties(clabs_static PROPERTIES OUTPUT_NAME "clabs")

add_library(clabs_shared SHARED ${CONTAINER_SRC})
target_include_directories(clabs_shared PUBLIC . ./container)
set_target_properties(clabs_shared PROPERTIES OUTPUT_NAME "clabs")
set_target_properties(clabs_shared PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

install(TARGETS clabs_static clabs_shared LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${CONTAINER_INC} DESTINATION include)

