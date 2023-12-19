cmake_minimum_required(VERSION 3.10)

# Add the executable VotingMethods
# add_executable(VotingMethods main.c)

# Add subdirectories
add_subdirectory(utils)
add_subdirectory(structures)
add_subdirectory(modules)

# main depends on modules and utils
add_executable(VotingMethods main.c)
target_link_libraries(VotingMethods PRIVATE modules)
