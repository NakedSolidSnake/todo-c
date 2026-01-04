add_library (task_repository_sqlite "")

target_sources (task_repository_sqlite
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_repository_sqlite.c
)

target_include_directories (task_repository_sqlite
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries (task_repository_sqlite
    PUBLIC
    domain
    ports
    sat
)