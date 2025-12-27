add_library (style "")

target_sources (style
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/style.c
)

target_include_directories (style
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)