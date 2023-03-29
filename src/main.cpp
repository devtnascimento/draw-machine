#include <iostream>
#include <string>
#include <vector>
#include "window.cpp"
#include "primitives/Triangle.cpp"

using namespace std;

int main(){

  Window window = Window(0, 0, 400, 400);

  vector <float> vertices {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f
  };

  string vs_path = "../shaders/vertex.glsl";
  string fs_path = "../shaders/fragment.glsl";


  if (!window.init())
    return -1;

  Triangle t = Triangle(vertices, vs_path, fs_path);
  window.event_loop();


  return 0;
}


