add_library (update)

target_sources (update
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_update_service.c
    ${CMAKE_CURRENT_LIST_DIR}/dto/task_update_request.c
)

target_include_directories (update
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dto
)

target_link_libraries (update
    PUBLIC
    domain
    common
)