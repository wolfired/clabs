include(ExternalProject)

ExternalProject_Add(
    ep_cmocka
    URL https://git.cryptomilk.org/projects/cmocka.git/snapshot/cmocka-1.1.5.tar.gz
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(ep_cmocka binary_dir)
ExternalProject_Get_Property(ep_cmocka source_dir)

add_library(cmocka SHARED IMPORTED GLOBAL)
set_property(TARGET cmocka PROPERTY IMPORTED_LOCATION "${binary_dir}/src/libcmocka.so")

add_dependencies(cmocka ep_cmocka)

set(CMOCKA_INCLUDE_DIR ${source_dir}/include GLOBAL)
