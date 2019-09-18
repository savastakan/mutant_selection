cmake_minimum_required(VERSION 3.13)
project(mut_project)

set(CMAKE_CXX_STANDARD 14)

file(GLOB project_SRC
        "*.h"
        "*.cpp"
        )
add_executable(mut_project ${project_SRC})