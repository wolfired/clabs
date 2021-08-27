find_program(PROGRAM_GCOVR gcovr)

set(CMAKE_C_FLAGS_CODECOV "-O0 -g --coverage" CACHE INTERNAL "")
mark_as_advanced(CMAKE_C_FLAGS_CODECOV)

link_libraries(gcov)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_CODECOV}")

add_custom_target(
    codecov
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Generating code cov report at ${PROJECT_BINARY_DIR}/codecov.xml"
    # 在 SHELL 中展示代码覆盖率总结
    COMMAND ${PROGRAM_GCOVR} --exclude-throw-branches -r .. --object-directory "${PROJECT_BINARY_DIR}" -e ".*/test/.*" -e ".*/usr/.*" --print-summary
    # 输出到 codecov.xml
    COMMAND ${PROGRAM_GCOVR} --xml --exclude-throw-branches -r .. --object-directory "${PROJECT_BINARY_DIR}" -e ".*/test/.*" -e ".*/usr/.*" -o codecov.xml
)
