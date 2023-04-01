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
            this->indices = indices;
            this->i_size = i_size;
        }
    private:
        int i_size;
        unsigned int* indices;

        void build(){

        }

    };

} // primitive