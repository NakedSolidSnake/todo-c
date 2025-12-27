add_subdirectory (models)

add_library (domain INTERFACE)

target_link_libraries(domain 
    INTERFACE
    models
)
