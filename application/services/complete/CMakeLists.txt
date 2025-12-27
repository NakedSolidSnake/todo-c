add_library (complete)

target_sources (complete
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_complete_service.c
    ${CMAKE_CURRENT_LIST_DIR}/dto/task_complete_request.c
)

target_include_directories (complete
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dto
)

target_link_libraries (complete
    PUBLIC
    domain
    common
)