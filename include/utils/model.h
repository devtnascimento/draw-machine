

#ifndef DRAW_MACHINE_MODEL_H
#define DRAW_MACHINE_MODEL_H

#include <concepts>
#include <vector>
#include <primitives/drawable.h>
#include <utils/movable.h>

template <typename T>
concept Model = std::is_base_of_v<Drawable, T> && std::is_base_of_v<Movable, T>;

template <Model T>
using ModelCollection = std::vector<T>;



#endif //DRAW_MACHINE_MODEL_H
