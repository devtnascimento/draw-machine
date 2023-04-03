#include "Triangle.cpp"
#include <cmath>
#include <boost/multi_array.hpp>

using namespace std;

namespace primitive {

    template <size_t v_n, size_t i_n>
    class Shape : public Triangle<v_n> {
    public:
        int color_loc{};
        unsigned int stride {};
        unsigned int offset {};
        boost::multi_array<float, 2> attributes {};
        Shape(
                auto vertices,
                size_t v_size,
                auto indices,
                size_t i_size,
                const string& vs_path,
                const string& fs_path
        ) : Triangle <v_n> (
                vertices,
                v_size,
                vs_path,
                fs_path
        ) {
            this->EBO = 0;
            this->indices = indices;
            this->i_size = i_size;
        }

        void build () override {
            cerr << "build" << endl;

            this->getShadersSources();
            this->compileShaders();
            this->linkProgram();

//            this->color_loc = glGetUniformLocation(this->program, "ourColor");
//            if (this->color_loc == -1) {
//                cerr << "[BUILD ERROR] COULD NOT GET UNIFORM LOCATION" << endl;
//                throw;
//            }
            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glGenBuffers(1, &this->EBO);
            glBindVertexArray(this->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->i_size, this->indices.data(), GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void draw() override {
            auto timeValue = static_cast<float>(glfwGetTime());
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            glUseProgram(this->program);
            glUniform4f(this->color_loc, 0.0f, greenValue, 0.0f, 1.0f);
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }


    private:
        size_t i_size{};
        boost::array<unsigned int, i_n> indices;
        unsigned int EBO{};

    };

} // primitive
