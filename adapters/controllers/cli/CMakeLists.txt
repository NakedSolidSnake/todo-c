add_library (cli "")

target_sources (cli
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/cli.c
)

target_include_directories (cli
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_directories (cli
    PUBLIC
    controller_base
    application
)