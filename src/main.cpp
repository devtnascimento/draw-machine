#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"
#include "primitives/drawable.cpp"
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

int main(){

    Window window = Window(400, 400);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    cout << fs::current_path() << endl;
    string vs_path = "../src/shaders/vertex.glsl";
    string fs_path = "../src/shaders/fragment.glsl";

    if (!window.init())
        return -1;

    vector<Drawable*> drawables;
    drawables.push_back(new Triangle(vertices, vs_path, fs_path));

    for (auto drawable : drawables){
        drawable->getLog();
    }

    int control_flow = not_infinity;
    window.event_loop(drawables, control_flow);




  return 0;
}


