#include <primitives/triangle.h>
#include <cmath>
#include <utils/texture.h>
#include <utils/movable.h>

#ifndef DRAW_MACHINE_SHAPE_H
#define DRAW_MACHINE_SHAPE_H

typedef Eigen::Matrix<unsigned int, Eigen::Dynamic, 3, Eigen::RowMajor> Indices;
typedef Eigen::Matrix<float, 4, 4, Eigen::RowMajor> Transform;

namespace primitive {
    class Shape : public Triangle, public movable::Movable {

    public:
        unsigned int offset{};
        utils::Texture* texture1{};
        utils::Texture* texture2{};
        Transform T{};
        Eigen::Vector3f center{};

        Shape(const Vertices& vertices, const Indices& indices,
              const std::string& vs_path, const std::string& fs_path
        );

        void build() override;
        void draw() override;
        void translate(const Eigen::Vector3f& point) override;
        void rotate(float angle, Eigen::Vector3f axis) override;
        void rotate(float angle) override;
        void move() override;

    private:
        GLsizeiptr i_size{};
        Indices indices{};
        unsigned int EBO{};
        GLsizei stride{};

    };

}

#endif
