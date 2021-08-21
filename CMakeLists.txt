cmake_minimum_required(VERSION 3.16)

project(clabs VERSION 0.0.1)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

add_subdirectory(src)
