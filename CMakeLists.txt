cmake_minimum_required(VERSION 3.7.0)
project (todo)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_BUILD_TYPE Debug)

function (create_test binary library)

    add_executable (${binary} ${CMAKE_CURRENT_LIST_DIR}/${binary}.c)
    target_link_libraries (${binary} PUBLIC ${library})
    add_test (NAME ${binary} COMMAND ${binary})
    set_target_properties (${binary} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests/)

endfunction ()

enable_testing ()

add_subdirectory (common)
add_subdirectory (domain)
add_subdirectory (application)