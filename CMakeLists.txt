cmake_minimum_required(VERSION 3.15)

project(draw-machine)

# add packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

# options interface
add_library(
  project_options
  INTERFACE
        primitives/shape.cpp include/primitives/shape.h)

add_library(
        glad
        INTERFACE
        primitives/shape.cpp include/primitives/shape.h
)
add_library(
        external
        INTERFACE
        include/external/stb_image.h
)

# set option c++23 version
target_compile_features(
  project_options
  INTERFACE
    cxx_std_23
)

file(GLOB executables 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h 
)

add_subdirectory(utils)
add_subdirectory(primitives)
add_executable(draw-machine ${executables})

target_sources(
  draw-machine
  PRIVATE
    src/main.cpp
    src/glad.c
    src/window.cpp
)

target_include_directories(
        draw-machine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(/usr/lib)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(    
  draw-machine
  PRIVATE
        ${OPENGL_LIBRARIES}
        glfw
        primitives
        glad
        project_options
        external
        utils
        Eigen3::Eigen
)
