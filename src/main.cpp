#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <array>
#include <Eigen/Geometry>

#include <primitives/triangle.h>
#include <primitives/drawable.h>
#include <primitives/shape.h>
#include <window.h>

namespace fs = std::filesystem;

using namespace std;

int main(){

    auto window = Window(800, 800);
    float v[] = {
            // positions          // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };

    Vertices vertices(4, 5);
    vertices  <<  0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                  0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
                 -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
                 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f;

    for (int i=0; i < vertices.size(); i++) {
        cout << vertices.data()[i] << " ";
    }
    cout << endl;
    for (float i : v) {
        cout << i << " ";
    }
    cout << endl;
    cout << "vertices: " << vertices.size() * sizeof(float) << endl;

    Indices indices(2, 3);
    indices <<  0, 1, 3,
                1, 2, 3;

    unsigned int idx[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    for (int i=0; i < indices.size(); i++) {
        cout << indices.data()[i] << " ";
    }
    cout << endl;
    for (unsigned int i : idx) {
        cout << i << " ";
    }
    cout << endl;


    cout << "CURRENT_PATH: " << fs::current_path() << endl;
    string vs_path = "../src/shaders/vertexT.glsl";
    string fs_path = "../src/shaders/fragmentT.glsl";

    if (!window.init())
        return -1;

    vector<primitive::Drawable*> drawables;

    auto* my_shape = new primitive::Shape(vertices, indices, vs_path, fs_path);

    Eigen::Vector3f offset;
    Eigen::Vector3f axis;
    float angle = 45.0f;

    drawables.emplace_back(my_shape);

    for (auto drawable : drawables) {
        drawable->build();
        drawable->getLog();
    }

    int control_flow = is_infinity;
    window.event_loop(drawables, control_flow);

  return 0;
}





