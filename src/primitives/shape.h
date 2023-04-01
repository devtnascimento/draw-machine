//
// Created by devtnascimento on 31/03/23.
//

#include <utility>

#include "Triangle.cpp"

#ifndef DRAW_MACHINE_SHAPE_H
#define DRAW_MACHINE_SHAPE_H

namespace primitive {

    class Shape : public Triangle {
        Shape(
                float* vertices,
                int v_size,
                unsigned int* indices,
                int i_size,
                string vs_path,
                string fs_path
        ) : Triangle(vertices,
                     v_size,
                     std::move(vs_path),
                     std::move(fs_path)){};

        void draw() override {};
        void getLog() override {};
        void setLog(const unsigned int&, const std::string&) override {};

        virtual ~Shape() = delete;
    private:
        unsigned int* indices{};
        int i_size{};





    };

} // primitive

#endif
