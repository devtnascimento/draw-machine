#include <window.h>

using namespace std;

Window::Window(int width, int height){
    this->width = width;
    this->height = height;
}

bool Window::init(){
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

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

  return true;
}

void Window::event_loop(ModelCollection<primitive::Shape>& shapes, int& control_flow) {

  unsigned int cont = 0;
  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto shape : shapes) {
      shape->draw();
    }
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (control_flow != is_infinity)
        break;
  }
}

Window::~Window(){
  glfwTerminate();
}

void Window::window_resize_handle(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}