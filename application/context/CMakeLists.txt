add_library (context "")

target_sources (context
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/todo.c
)

target_include_directories (context
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (context
    PUBLIC
    domain
    complete
    create
    remove
    update
)

