cmake_minimum_required(VERSION 3.15)

project(utils)

file(GLOB utils_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(utils ${utils_sources})

target_sources(
        utils
        PRIVATE
        ${utils_sources}
)

target_include_directories(
        utils
        PUBLIC
        .
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
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


