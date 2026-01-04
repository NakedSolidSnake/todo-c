add_library (factory_repository "")

target_sources (factory_repository
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/factory_repository.c
)

target_include_directories (factory_repository
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (factory_repository
    PUBLIC
    task_repository_memory
    task_repository_sqlite
    config
)