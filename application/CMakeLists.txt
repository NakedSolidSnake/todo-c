add_subdirectory (ports)
add_subdirectory (services)
add_subdirectory (context)

add_library (application INTERFACE)

target_link_libraries (application 
    INTERFACE
    context
)
