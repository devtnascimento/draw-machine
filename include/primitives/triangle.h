
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <primitives/drawable.h>
#include <Eigen/Geometry>

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>  Vertices;

namespace primitive {
    class Triangle : public Drawable {
    public:
        GLuint VBO{}, VAO{}, program{}, VS{}, FS{};
        GLint start_index{};
        std::string vs_src, fs_src;
        std::vector<std::string> log;
        GLFWwindow* context{};
        Vertices vertices{};

        Triangle();
        void draw() override;
        void build() override;
        void getLog() override;

    protected:
        GLsizeiptr size{};
        std::string vs_path, fs_path;

        void getShadersSources();
        void compileShaders();
        void deleteShaders();
        void linkProgram();
        void setLog(const unsigned int &object, const std::string &log_type) override;
    };
}

#endif


