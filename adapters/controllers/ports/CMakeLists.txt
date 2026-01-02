add_library (controller_base INTERFACE)

target_include_directories (controller_base
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries (controller_base
    INTERFACE
    sat
    config
)