add_library (task_repository_memory "")

target_sources (task_repository_memory
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_repository_memory.c
)

target_include_directories (task_repository_memory
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries (task_repository_memory
    PUBLIC
    domain
    ports
)