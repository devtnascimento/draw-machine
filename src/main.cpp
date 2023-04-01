#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"
#include "primitives/drawable.cpp"
#include "primitives/shape.cpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(){

    Window window = Window(800, 800);

    float triangle_vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    float rectangle_vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {
            0, 1, 3,  //first triangle
            1, 2, 3  // second triangle
    };

    cout << "CURRENT_PATH: " << fs::current_path() << endl;
    string vs_path = "../shaders/vertex.glsl";
    string fs_path = "../shaders/fragment.glsl";

    if (!window.init())
        return -1;

    vector<Drawable*> drawables;
    //drawables.push_back(new Triangle(triangle_vertices, sizeof(triangle_vertices), vs_path, fs_path));
    drawables.push_back(new primitive::Shape(rectangle_vertices, sizeof(rectangle_vertices), indices, sizeof(indices), vs_path, fs_path));

    for (auto drawable : drawables){
        drawable->build();
        drawable->getLog();
    }

    int control_flow = is_infinity;
    window.event_loop(drawables, control_flow);

  return 0;
}





