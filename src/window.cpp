#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>

using namespace std;

class Window {

  private:
  vector<int> options;
  GLFWwindow* window;
  unsigned int xi, yi, width, height;

  static void window_resize_handle(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
  }

  public:

  Window(unsigned int xi, unsigned int yi, unsigned int width, unsigned int height){

    this->xi = xi;
    this->yi = yi;
    this->width = width;
    this->height = height;
  }

  bool init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(width, height, "ogl", NULL, NULL);
    if (this->window == NULL){
      cerr << "Failed to create GLFW window" << endl;
      glfwTerminate();
      return false;
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
      cerr << "Failed to initialize GLAD" << endl;
      glfwTerminate();
      return false;
    }

    glfwSetFramebufferSizeCallback(this->window, this->window_resize_handle);
    return true;
  }

  void event_loop(){
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
  }

  ~Window(){
    glfwTerminate();
  }

};





