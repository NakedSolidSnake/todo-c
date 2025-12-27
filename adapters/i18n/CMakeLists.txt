add_library (translate "")
target_sources (translate
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}/translate.c
)

target_include_directories (translate
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
)