add_library (web "")

target_sources (web
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/web.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/health/handler_health.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/complete/handler_complete.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/create/handler_create.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/display/handler_display.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/remove/handler_remove.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/shutdown/handler_shutdown.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/update/handler_update.c
    ${CMAKE_CURRENT_LIST_DIR}/handlers/schema/handler_schema.c

    ${CMAKE_CURRENT_LIST_DIR}/utils/web_send.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/web_response.c
)

target_include_directories (web
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/handlers/health
    ${CMAKE_CURRENT_LIST_DIR}/handlers/complete
    ${CMAKE_CURRENT_LIST_DIR}/handlers/create
    ${CMAKE_CURRENT_LIST_DIR}/handlers/create/dto
    ${CMAKE_CURRENT_LIST_DIR}/handlers/display
    ${CMAKE_CURRENT_LIST_DIR}/handlers/remove
    ${CMAKE_CURRENT_LIST_DIR}/handlers/shutdown
    ${CMAKE_CURRENT_LIST_DIR}/handlers/update
    ${CMAKE_CURRENT_LIST_DIR}/handlers/update/dto
    ${CMAKE_CURRENT_LIST_DIR}/handlers/schema

    ${CMAKE_CURRENT_LIST_DIR}/utils
)

target_link_libraries (web
    PUBLIC
    controller_base
    application
    translate
)