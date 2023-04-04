#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"
#include "primitives/drawable.cpp"
#include "primitives/shape.cpp"
#include <filesystem>
#include "utils/vertices.cpp"
#include <array>


//#include <boost/algorithm/cxx17/for_each_n.hpp>

namespace fs = std::filesystem;

using namespace std;

namespace vtx = utils::vertex;

int main(){

    Window window = Window(800, 800);


    array<float, 32> vertices = {
                      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    array<unsigned int, 6> indices {{
                0, 1, 3,
                1, 2, 3
    }};

    cout << "CURRENT_PATH: " << fs::current_path() << endl;
    string vs_path = "../shaders/vertex3.glsl";
    string fs_path = "../shaders/fragment3.glsl";

    if (!window.init())
        return -1;

    vector<Drawable*> drawables;

    constexpr size_t v_size = 32;
    constexpr size_t i_size = 6;

    cout << "size: " << sizeof(vertices) << endl << "size data: " << sizeof(vertices.data()) << endl;

    drawables.push_back(new primitive::Shape<v_size, i_size>(vertices, sizeof(vertices), indices, sizeof(indices), vs_path, fs_path));

    for (auto drawable : drawables) {
        drawable->build();
        drawable->getLog();
    }

    int control_flow = is_infinity;
    window.event_loop(drawables, control_flow);

  return 0;
}





