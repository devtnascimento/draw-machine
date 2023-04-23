#pragma once

#include <concepts>
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <array>
#include <Eigen/Geometry>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>

#include <dirent.h>
#include <algorithm>
#include <external/stb_image.h>

#include <primitives/drawable.h>
#include <utils/movable.h>

#define PATH std::string("/home/devtnascimento/workspace/cpp/draw-machine")

template <typename T>
concept Model2D = std::is_base_of_v<primitive::Drawable, T> || std::is_base_of_v<movable::Movable, T>;

template <typename T>
using ModelCollection = std::vector<T*>;

