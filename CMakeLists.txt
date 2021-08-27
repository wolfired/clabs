cmake_minimum_required(VERSION 3.16)

project(clabs VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ./cmake/modules)

include(codecov)
include(ep_cmocka)

enable_testing()

find_program(PROGRAM_CCACHE ccache)
if(PROGRAM_CCACHE)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${PROGRAM_CCACHE}")
endif()

add_subdirectory(src)
