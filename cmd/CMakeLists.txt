add_executable (todoc "")
    
target_sources (todoc
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/factory/todo_factory.c
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_include_directories (todoc
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/factory
)

target_link_libraries (todoc
    PUBLIC
    cli
    task_repository_memory
    web
)