add_executable(
    test_wasm
    test_wasm.c
)

if(${ENABLE_WASM} STREQUAL "true")
    if(${ENABLE_WASM_HTML} STREQUAL "true")
        set_target_properties(
            test_wasm 
            PROPERTIES 
                OUTPUT_NAME "test_wasm"
                SUFFIX ".html"
        )
    endif()
endif()
