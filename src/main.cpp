#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"
#include "primitives/drawable.cpp"
#include "primitives/shape.h"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(){

    Window window = Window(800, 800);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    cout << "CURRENT_PATH: " << fs::current_path() << endl;
    string vs_path = "../shaders/vertex.glsl";
    string fs_path = "../shaders/fragment.glsl";

    if (!window.init())
        return -1;

    vector<Drawable*> drawables;
    drawables.emplace_back(new Triangle(vertices, sizeof(vertices), vs_path, fs_path));

    for (auto drawable : drawables){
        drawable->getLog();
    }

    int control_flow = is_infinity;



    window.event_loop(drawables, control_flow);

  return 0;
}


