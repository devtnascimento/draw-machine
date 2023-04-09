#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "drawable.cpp"
#include <Eigen/Geometry>

using namespace std;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>  Vertices;

namespace primitive {
    class Triangle : public Drawable {

    public:
        GLuint VBO{}, VAO{}, program{}, VS{}, FS{};
        GLint start_index{};
        string vs_src, fs_src;
        vector<string> log;
        GLFWwindow* context{};
        Vertices vertices{};

        Triangle() = default;

        void draw() override {
            if (this->context == nullptr)
                cout << "Invalid context" << endl;
            glUseProgram(this->program);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, this->start_index, 3);
        }

        void build() override {
            this->getShadersSources();
            this->compileShaders();
            this->linkProgram();
            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glBindVertexArray(this->VAO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

            glEnableVertexAttribArray(0);
            glBindVertexArray(0);
        }

    protected:
        GLsizeiptr size{};
        string vs_path, fs_path;

        void getShadersSources() {
            fstream vs_file;
            fstream fs_file;
            vs_file.open(this->vs_path);
            fs_file.open(this->fs_path);

            if (!vs_file.is_open()) {
                throw runtime_error("Failed to open vertex shader");
            }
            if (!fs_file.is_open()) {
                throw runtime_error("Failed to open fragment shader");
            }
            stringstream vs_buffer, fs_buffer;
            vs_buffer << vs_file.rdbuf();
            fs_buffer << fs_file.rdbuf();

            vs_file.close();
            fs_file.close();

            this->vs_src = std::move(vs_buffer.str());
            this->fs_src = std::move(fs_buffer.str());
        }

        void compileShaders() {
            this->VS = glCreateShader(GL_VERTEX_SHADER);

            const char *vsrc = this->vs_src.c_str();
            glShaderSource(this->VS, 1, &vsrc, nullptr);
            glCompileShader(this->VS);

            const char *fsrc = this->fs_src.c_str();
            this->FS = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(this->FS, 1, &fsrc, nullptr);
            glCompileShader(this->FS);

            this->setLog(this->VS, "VS_SHADER");
            this->setLog(this->FS, "FS_SHADER");
        }

        void deleteShaders() {
            glDeleteShader(this->VS);
            glDeleteShader(this->FS);
            this->VS = 0;
            this->FS = 0;
        }

        void linkProgram() {
            this->program = glCreateProgram();
            glAttachShader(this->program, this->VS);
            glAttachShader(this->program, this->FS);
            glLinkProgram(this->program);
            this->setLog(this->program, "PROGRAM");
            this->deleteShaders();
        }

        void getLog() override {
            for (const string &msg: this->log) {
                cout << "[TRIANGLE] " << msg << endl;
            }
        }

        void setLog(const unsigned int &object, const string &log_type) override {
            int success;
            if (log_type == "PROGRAM") {
                char infoLog[512];
                glGetProgramiv(object, GL_LINK_STATUS, &success);
                if (!success) {
                    glGetProgramInfoLog(object, 512, nullptr, infoLog);
                    string log_(infoLog);
                    string s = "[" + log_type + "] ";
                    if (!log_.empty())
                        this->log.emplace_back(s + log_);
                    for (const auto &err: this->log)
                        cout << err << endl;
                    cerr << "Coud not link program" << this->program <<
                         " for shaders (" << this->VS << "," << this->FS << ")" << endl;
                }
            } else if (log_type == "VS_SHADER" || log_type == "FS_SHADER") {
                cout << object << endl;
                glGetShaderiv(object, GL_COMPILE_STATUS, &success);
                if (!success) {
                    GLint log_size;
                    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_size);
                    cout << "logsize: " << log_size << endl;
                    GLenum error = glGetError();
                    if (error != GL_NO_ERROR) {
                        switch (error) {
                            case GL_INVALID_ENUM:
                                std::cerr << "OpenGL error: Invalid enum" << std::endl;
                                break;
                            case GL_INVALID_VALUE:
                                std::cerr << "OpenGL error: Invalid value" << std::endl;
                                break;
                            case GL_INVALID_OPERATION:
                                std::cerr << "OpenGL error: Invalid operation" << std::endl;
                                break;
                            case GL_STACK_OVERFLOW:
                                std::cerr << "OpenGL error: Stack overflow" << std::endl;
                                break;
                            case GL_STACK_UNDERFLOW:
                                std::cerr << "OpenGL error: Stack underflow" << std::endl;
                                break;
                            case GL_OUT_OF_MEMORY:
                                std::cerr << "OpenGL error: Out of memory" << std::endl;
                                break;
                            default:
                                std::cerr << "Unknown OpenGL error" << std::endl;
                                break;
                        }
                    }
                    GLchar infoLog[log_size];
                    glGetShaderInfoLog(object, log_size, nullptr, infoLog);
                    string log_(infoLog);
                    string s = "[" + log_type + "] ";
                    this->log.emplace_back(s + log_);
                    for (const auto &err: this->log)
                        cout << err << endl;
                    throw runtime_error("Could not compile shader");
                }
            }
        }
    };
}

