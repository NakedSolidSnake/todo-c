add_library (menu "")

target_sources (menu
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/menu.c
)

target_include_directories (menu
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)

target_link_libraries (menu
    PUBLIC
    translate
)