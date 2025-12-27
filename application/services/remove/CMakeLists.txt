add_library (remove)

target_sources (remove
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_remove_service.c
    ${CMAKE_CURRENT_LIST_DIR}/dto/task_remove_request.c
)

target_include_directories (remove
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/dto
)

target_link_libraries (remove
    PUBLIC
    domain
    common
    ports
)