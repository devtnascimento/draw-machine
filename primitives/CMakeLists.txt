cmake_minimum_required(VERSION 3.15)

project(primitives)


file(GLOB primitives_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(primitives ${primitives_sources})

target_sources(
  primitives
  PRIVATE
        ${primitives_sources}
)

target_include_directories(
    primitives
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
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


