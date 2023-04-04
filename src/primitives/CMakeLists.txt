cmake_minimum_required(VERSION 3.15)

project(primitives)

add_library(primitives shape.cpp ../include/primitives/shape.h drawable3D.cpp drawable3D.h)

target_sources(
  primitives
  PRIVATE
        Triangle.cpp
        shape.cpp
        drawable.cpp
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
        utils
        external
        project_options
)


