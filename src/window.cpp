#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>
#include <functional>
#include <tuple>
#include <utility>
#import "primitives/drawable.cpp"

#define is_infinity (-1)
#define not_infinity (2)


using namespace std;

class Window {

  private:
  vector<int> options;
  GLFWwindow* window;
  int width, height;

  static void window_resize_handle(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
  }

  public:
  Window(int width, int height){
    this->width = width;
    this->height = height;
  }

  bool init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(this->width, this->height, "ogl", nullptr, nullptr);
    if (this->window == nullptr){
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

    glfwSetFramebufferSizeCallback(this->window, window_resize_handle);
    return true;
  }

  void event_loop(vector<Drawable*> &drawables, int &control_flow){
      unsigned int cont = 0;
      bool condition;
      while(!glfwWindowShouldClose(window) && condition){
          condition = (control_flow == is_infinity) || (cont < control_flow);
          glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          if (glad_glDrawArrays == nullptr)
              cout << "Nao Carregou!" << endl;
          drawables[0]->draw();
          if (glad_glDrawArrays != nullptr)
              cout << "Carregou!" << endl;
          //for (auto &drawable : drawables) {
          //    drawable->draw();
          //}
          glfwSwapBuffers(window);
          glfwPollEvents();
          if (cont < control_flow)
            cont++;
      }
  }

  ~Window(){
    glfwTerminate();
  }

};





