project(DataStructures)
add_library(data_structures matrix.c matrix.h)
target_link_libraries(data_structures PUBLIC utils)
target_include_directories(data_structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})