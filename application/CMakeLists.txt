add_subdirectory (services)
# add_subdirectory (context)

target_include_directories (domain
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/ports
)