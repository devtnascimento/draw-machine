cmake_minimum_required(VERSION 3.15)

project(utils)

add_library(utils shaders.cpp Texture.cpp transforms.cpp)

target_sources(
        utils
        PRIVATE
        shaders.cpp
        Texture.cpp
)

target_include_directories(
        utils
        PUBLIC
        .
        ../include
)

find_package(Eigen3 REQUIRED)

link_directories(/usr/lib)
target_link_libraries(
        utils
        PRIVATE
        OpenGL::GL
        glad
        external
        project_options
        Eigen3::Eigen
)


