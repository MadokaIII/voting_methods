cmake_minimum_required(VERSION 3.20)

# Add the executable VotingMethods
# add_executable(VotingMethods main.c)

# Add subdirectories
add_subdirectory(utils)
add_subdirectory(structures)
# add_subdirectory(modules)

# main depends on modules and utils
# target_link_libraries(VotingMethods PRIVATE modules)