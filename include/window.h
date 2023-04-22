#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <primitives/drawable.h>
#include <primitives/triangle.h>

#define is_infinity (-1)
#define not_infinity (2)

class Window {
public:
    Window(int width, int height);
    bool init();
    void event_loop(std::vector<primitive::Drawable*>& drawables, int& control_flow);
    ~Window();
private:
    std::vector<int> options;
    GLFWwindow* window;
    int width, height;
    static void window_resize_handle(GLFWwindow* window, int width, int height);
};

#endif
