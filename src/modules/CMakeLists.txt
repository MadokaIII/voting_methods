project(Modules)
add_library(modules place_holder.c place_holder.h)
target_link_libraries(modules PUBLIC utils data_structures)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
