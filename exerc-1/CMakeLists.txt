cmake_minimum_required(VERSION 3.10)

# set the project name
project(exerc1)

# add the executables
add_executable(sort sort.c) 
add_executable(sort-o sort-o.c)

target_link_libraries(sort) 
