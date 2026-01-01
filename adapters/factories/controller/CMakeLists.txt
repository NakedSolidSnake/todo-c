add_library (factory_controller "")

target_sources (factory_controller
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/factory_controller.c
)

target_include_directories (factory_controller
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (factory_controller
    PUBLIC
    controller_base
    cli
    web
)