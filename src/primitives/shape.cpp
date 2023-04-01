#include <algorithm>
#include "Triangle.cpp"

using namespace std;

namespace primitive {

    class Shape : public Triangle {
    public:
        Shape(
                float *vertices,
                int v_size,
                unsigned int* indices,
                int i_size,
                string vs_path,
                string fs_path
        ) : Triangle(
                vertices,
                v_size,
                std::move(vs_path),
                std::move(fs_path)
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

            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glGenBuffers(1, &this->EBO);
            glBindVertexArray(this->VAO);

            cout << "size: " << this->size << endl;
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->size, this->vertices, GL_STATIC_DRAW);

            cout << "i_size: " << this->i_size << endl;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->i_size, this->indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void draw() override {
            glUseProgram(this->program);
            glBindVertexArray(this->VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

    private:
        int i_size;
        unsigned int* indices;
        unsigned int EBO;

    };

} // primitive