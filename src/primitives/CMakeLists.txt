cmake_minimum_required(VERSION 3.15)

project(primitives)

add_library(primitives shape.cpp ../include/primitives/shape.h drawable3D.cpp ../include/drawable3D.h)

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

find_package(Eigen3 REQUIRED)

target_link_libraries(    
  primitives
  PRIVATE
        OpenGL::GL
        glad
        utils
        external
        project_options
        Eigen3::Eigen
)


