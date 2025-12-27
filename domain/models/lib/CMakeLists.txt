add_library (models "")

target_sources (models
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/task/task.c
)

target_include_directories (models
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/task
)

target_link_libraries (models 
    PUBLIC
    sat
)