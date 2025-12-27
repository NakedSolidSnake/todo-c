add_library (create)

target_sources (create
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/task_create_service.c
    ${CMAKE_CURRENT_LIST_DIR}/dto/task_create_request.c
)

target_include_directories (create
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dto
)

target_link_libraries (create
    PUBLIC
    domain
    common
)