add_library(structures matrix.c matrix.h)
target_link_libraries(structures PUBLIC utils)
target_include_directories(structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
