add_library (config "")

target_sources (config
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/config.c
)

target_include_directories (config
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (config
    PUBLIC
    sat
)