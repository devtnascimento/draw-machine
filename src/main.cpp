#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"
#include "primitives/drawable.cpp"
#include "primitives/shape.cpp"
#include <filesystem>
#include <boost/array.hpp>
#include <boost/assign.hpp>
#include <boost/range/size.hpp>
//#include <boost/algorithm/cxx17/for_each_n.hpp>

namespace fs = std::filesystem;

using namespace std;

int main(){

     Window window = Window(800, 800);

    boost::array<const float, 24> vertices = {{
            // positions                       // colors
            0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,   // bottom right
            0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f,   // bottom left
            -0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f
    }};

//    boost::array<const float, 12> vertices = {{
//                    0.5f,0.5f,0.0f,
//                    0.5f,-0.5f,0.0f,
//                    -0.5f,-0.5f,0.0f,
//                    -0.5f,0.5f,0.0f
//    }};

     boost::array<const unsigned int, 6> indices {{
                    0, 1, 3,
                    1, 2, 3
    }};

    cout << "CURRENT_PATH: " << fs::current_path() << endl;
    string vs_path = "../shaders/vertex2.glsl";
    string fs_path = "../shaders/fragment2.glsl";

    if (!window.init())
        return -1;

    vector<Drawable*> drawables;
    //drawables.push_back(new Triangle(triangle_vertices, sizeof(triangle_vertices), vs_path, fs_path));
    size_t v_size = boost::size(vertices);

    cout << "v_size: " << v_size << endl;

    drawables.push_back(new primitive::Shape<24, 6>(vertices, sizeof(vertices), indices, sizeof(indices), vs_path, fs_path));

    for (auto drawable : drawables) {
        drawable->build();
        drawable->getLog();
    }

    int control_flow = is_infinity;
    window.event_loop(drawables, control_flow);

  return 0;
}





