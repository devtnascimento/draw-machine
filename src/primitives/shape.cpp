#include "Triangle.cpp"
#include <cmath>
#include <array>
#include "../utils/Texture.cpp"


using namespace std;

namespace primitive {

    struct Attribute{
        unsigned int index, size, stride, offset;
        bool normalized;
        Attribute(unsigned int index, unsigned int size, bool normalized, unsigned int stride, unsigned int offset)
                : index(index), size(size), normalized(normalized), stride(stride), offset(offset) {}
    };

    template <size_t v_n, size_t i_n>
    class Shape : public Triangle<v_n> {
    public:
        int color_loc{};
        unsigned int stride{};
        unsigned int offset{};
        utils::Texture* texture1{};
        utils::Texture* texture2{};

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
            this->texture1 = new utils::Texture("container", GL_RGB);
            this->texture2 = new utils::Texture("awesomeface", GL_RGBA, true);
        }

        void build () override {

            this->getShadersSources();
            this->compileShaders();
            this->linkProgram();

            this->color_loc = glGetUniformLocation(this->program, "ourTexture");
            if (this->color_loc == -1) {
                cerr << "[BUILD] COULD NOT GET UNIFORM LOCATION" << endl;
            }

            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glGenBuffers(1, &this->EBO);
            glBindVertexArray(this->VAO);

            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->i_size, this->indices.data(), GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            // color attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);

            // texture attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glUseProgram(this->program);
            glUniform1i(glGetUniformLocation(this->program, "texture1"), 0);
            glUniform1i(glGetUniformLocation(this->program, "texture2"), 1);

        }

        void draw() override {

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture1->id);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, this->texture2->id);

            glUseProgram(this->program);
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }


    private:
        size_t i_size{};
        array<unsigned int, i_n> indices;
        unsigned int EBO{};
    };

} // primitive
