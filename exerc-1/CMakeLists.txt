cmake_minimum_required(VERSION 3.10)

# set the project name
project(exerc1)

add_compile_options("-Wall" "-g")

# add the executable
add_executable(sort sort-o.c) 

target_link_libraries(sort) 
