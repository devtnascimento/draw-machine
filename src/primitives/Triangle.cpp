#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "../glad/glad.h"
#include <functional>
#include "drawable.cpp"


using namespace std;

class Triangle : public Drawable {

    public:
        GLuint VBO{}, VBA{}, VAO{}, loc{}, program{}, VS{}, FS{};
        GLint start_index;
        vector <const char*> shaders_src;
        vector <string> log;

        Triangle(const float* vertices, string vs_path, string fs_path){
            this->vertices = vertices;
            this->vs_path = std::move(vs_path);
            this->fs_path = std::move(fs_path);
            this->start_index = 0;
            if (!this->vs_path.empty() && !this->fs_path.empty())
                this->build();
        }

        void draw() override {
            cout << "[" << __func__ << "] vao: " << this->VAO << endl;
            glUseProgram(this->program);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, this->start_index, 3);
        }

        const char* getVsSource(){
            return this->getShadersSources()[0];
        }

        const char* getFsSource(){
            return this->getShadersSources()[1];
        }

    private:
        const float* vertices;
        string vs_path, fs_path;

        vector <const char*> getShadersSources(){
            fstream vs_file;
            fstream fs_file;
            vs_file.open(this->vs_path);
            fs_file.open(this->fs_path);

            if (!vs_file.is_open()){
                throw runtime_error("Failed to open vertex shader");
            }
            if (!fs_file.is_open()){
                throw runtime_error("Failed to open fragment shader");
            }
            stringstream vs_buffer, fs_buffer;
            vs_buffer << vs_file.rdbuf();
            fs_buffer << fs_file.rdbuf();

            vs_file.close();
            fs_file.close();

            string vs_str = std::move(vs_buffer.str());
            string fs_str = std::move(fs_buffer.str());

            return vector {vs_str.c_str(), fs_str.c_str()};
        }

        void build(){
            glGenBuffers(1, &this->VBO);
            glGenVertexArrays(1, &this->VAO);
            glBindVertexArray(this->VAO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
            this->shaders_src = this->getShadersSources();
            this->compileShaders();
            this->linkProgram();
            glVertexAttribPointer(this->loc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void compileShaders(){
            const char *vertexShaderSource = "#version 330 core\n"
                                             "layout (location = 0) in vec3 aPos;\n"
                                             "void main()\n"
                                             "{\n"
                                             "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                             "}\0";

            this->VS = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(this->VS, 1,  &vertexShaderSource, nullptr);
            glCompileShader(GL_VERTEX_SHADER);

            const char *fragmentShaderSource = "#version 330 core\n"
                                             "out vec4 FragColor\n"
                                             "void main()\n"
                                             "{\n"
                                             "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                             "}\0";

            this->FS = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(this->FS, 1, &fragmentShaderSource, nullptr);
            glCompileShader(GL_FRAGMENT_SHADER);

            cout <<"[" << __func__ << "]" << this->VS << endl;
            int sucess = 0;
            this->setLog(this->VS, "SHADER");
            this->setLog(this->FS, "SHADER");
        }

        void deleteShaders() const {
            glDeleteShader(this->VS);
            glDeleteShader(this->FS);
        }

        void linkProgram(){
            cout << "[" << __func__ << "] VS: " << this->VS << endl;
            cout << "[" << __func__ << "] FS: " << this->FS << endl;
            this->program = glCreateProgram();
            glAttachShader(this->program, this->VS);
            glAttachShader(this->program, this->FS);
            glLinkProgram(this->program);
            this->setLog(this->program, "PROGRAM");
            this->deleteShaders();
        }

        void getLog() override{
            for (const string& msg : this->log){
                cout << "[TRIANGLE] " << msg << endl;
            }
        }

        void setLog(const unsigned int& object, const string& log_type) override {
            int success;
            if (log_type == "PROGRAM"){
                char infoLog[512];
                glGetProgramiv(object, GL_LINK_STATUS, &success);
                if (!success){
                    glGetProgramInfoLog(object, 512, nullptr, infoLog);
                    string log_(infoLog);
                    string s = "[" + log_type + "] ";
                    if (!log_.empty())
                        this->log.emplace_back(s + log_);
                    for (const auto& err : this->log)
                        cout << err << endl;
                    throw runtime_error("Coud not link program");
                }
            }
            else if (log_type == "SHADER"){
                cout << object << endl;
                glGetShaderiv(object, GL_COMPILE_STATUS, &success);
                if (!success){
                    GLint log_size;
                    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_size);
                    cout << "logsize: " << log_size << endl;
                    GLenum error = glGetError();
                    cout << error << endl;
                    while (error != GL_NO_ERROR) {
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
                                // Add more cases for other error codes as needed...
                            default:
                                std::cerr << "Unknown OpenGL error" << std::endl;
                                break;
                        }
                        error = glGetError();
                    }
                    GLchar infoLog[log_size];
                    glGetShaderInfoLog(object, log_size, nullptr, infoLog);
                    string log_(infoLog);
                    string s = "[" + log_type + "] ";
                    this->log.emplace_back(s + log_);
                    for (const auto& err : this->log)
                        cout << err << endl;
                    cout << "glGetShaderInfoLog return status code: " << success << endl;
                    throw runtime_error("Could not compile shader program");
                }
            }
        }
};


