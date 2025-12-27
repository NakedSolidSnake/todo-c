add_library (prompt "")

target_sources (prompt
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/prompt.c
)

target_include_directories (prompt
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (prompt
    PUBLIC
    application
    style
)