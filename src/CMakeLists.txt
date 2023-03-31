cmake_minimum_required(VERSION 3.15)

project(draw-machine)

# set bin output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)
message("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# add packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
# commom libraries
add_subdirectory(glad)

# options interface
add_library(
  project_options
  INTERFACE
)

# set option c++20 version 
target_compile_features(
  project_options
  INTERFACE
    cxx_std_23
)

add_subdirectory(primitives)
add_executable(draw-machine window.cpp window.h)

target_sources(
  draw-machine
  PRIVATE
    main.cpp
    glad.c
    window.cpp
)

target_include_directories(
        draw-machine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glad
)

target_link_libraries(    
  draw-machine
  PRIVATE
  ${OPENGL_LIBRARIES}
    glfw
    primitives
    glad
    project_options
)





