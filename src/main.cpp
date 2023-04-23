#define STB_IMAGE_IMPLEMENTATION

#include <utils/model.h>
#include <primitives/triangle.h>
#include <primitives/shape.h>
#include <window.h>


using namespace std;

int main(){

    auto window = Window(800, 800);

    Vertices vertices(4, 5);
    vertices  <<  0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                  0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
                 -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
                 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f;

    Indices indices(2, 3);
    indices <<  0, 1, 3,
                1, 2, 3;

    string vs_path = PATH + "/src/shaders/vertexT.glsl";
    string fs_path = PATH + "/src/shaders/fragmentT.glsl";

    if (!window.init())
        return -1;

    ModelCollection<primitive::Shape> shapes;

    shapes.push_back(new primitive::Shape(vertices, indices, vs_path, fs_path));

    for (auto shape : shapes) {
        shape->build();
        shape->getLog();
    }

    int control_flow = is_infinity;
    window.event_loop(shapes, control_flow);    

  return 0;
}





