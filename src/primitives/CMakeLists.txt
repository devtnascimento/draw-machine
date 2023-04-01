cmake_minimum_required(VERSION 3.15)

project(primitives)

add_library(primitives shape.cpp shape.h)

target_sources(
  primitives
  PUBLIC
    Triangle.hpp
  PRIVATE
    Triangle.cpp
)

target_include_directories(
    primitives
    PUBLIC
        .
        ../include
)


target_link_libraries(    
  primitives
  PRIVATE
        OpenGL::GL
        glad
        project_options
)


