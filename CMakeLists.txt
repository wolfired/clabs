cmake_minimum_required(VERSION 3.10)

# SHARED
# STATIC
add_library(
    bridge
    SHARED
    src/go2v8/bridge.hpp
    src/go2v8/bridge.cpp
    src/go2v8/V8Hub.hpp
    src/go2v8/V8Hub.cpp
    src/go2v8/VMHub.hpp
    src/go2v8/VMHub.cpp
)
target_include_directories(
    bridge
    PRIVATE /home/link/workspace_git/elgoog/v8/v8
    PRIVATE /home/link/workspace_git/elgoog/v8/v8/include
)

add_library(
    go2v8
    SHARED
    src/go2v8/go2v8.h
    src/go2v8/go2v8.c
)
target_link_libraries(
    go2v8
    bridge
)

# add_library(cmdie src/cmdie.h src/cmdie.c)

add_executable(
    main
    src/main.c
)

find_library(
    V8
    v8
    /home/link/workspace_git/elgoog/v8/v8/out.gn/x64.release_shared_nosnapshots
)
find_library(
    V8_LIBBASE
    v8_libbase
    /home/link/workspace_git/elgoog/v8/v8/out.gn/x64.release_shared_nosnapshots
)
find_library(
    V8_LIBPLATFORM
    v8_libplatform
    /home/link/workspace_git/elgoog/v8/v8/out.gn/x64.release_shared_nosnapshots
)
find_library(
    ICUUC
    icuuc
    /home/link/workspace_git/elgoog/v8/v8/out.gn/x64.release_shared_nosnapshots
)
find_library(
    ICUI18N
    icui18n
    /home/link/workspace_git/elgoog/v8/v8/out.gn/x64.release_shared_nosnapshots
)
target_link_libraries(
    main
    go2v8
    bridge
    ${V8}
    ${V8_LIBBASE}
    ${V8_LIBPLATFORM}
    ${ICUUC}
    ${ICUI18N}
    rt
    dl
    pthread
)
