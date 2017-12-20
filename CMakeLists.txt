add_library(cmdie src/cmdie.h src/cmdie.c)
add_executable(main src/main.c)
target_link_libraries(main cmdie)
