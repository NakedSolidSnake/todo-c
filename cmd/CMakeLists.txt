add_executable (todoc "")
    
target_sources (todoc
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

target_include_directories (todoc
    PUBLIC
)

target_link_libraries (todoc
    PUBLIC
    task_repository_memory
    factory_controller
)