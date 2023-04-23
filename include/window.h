#pragma once

#include <utils/model.h>
#include <primitives/shape.h>

#define is_infinity (-1)
#define not_infinity (2)

class Window {
public:
    Window(int width, int height);
    bool init();
    void event_loop(ModelCollection<primitive::Shape>& shapes, int& control_flow);
    ~Window();
private:
    std::vector<int> options;
    GLFWwindow* window;
    int width, height;
    static void window_resize_handle(GLFWwindow* window, int width, int height);
};
