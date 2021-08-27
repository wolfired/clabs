include(ExternalProject)

ExternalProject_Add(
    ep_cmocka
    PREFIX /home/link/workspace_git/clabs/ep_cmocka
    URL https://git.cryptomilk.org/projects/cmocka.git/snapshot/cmocka-1.1.5.tar.gz
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=/home/link/workspace_git/clabs/ep_cmocka
)
