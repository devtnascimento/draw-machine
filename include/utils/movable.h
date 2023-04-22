//
// Created by devtnascimento on 20/04/23.
//

#ifndef DRAW_MACHINE_MOVABLE_H
#define DRAW_MACHINE_MOVABLE_H

#include <Eigen/Geometry>
#include <iostream>
#include <utility>

namespace movable {

    class Movable {
    public:
        virtual void translate(const Eigen::Vector3f& point) = 0;
        virtual void rotate(float, Eigen::Vector3f) = 0;
        virtual void rotate(float) = 0;
        virtual void move() = 0;
    };

    class Object : public Movable {
    public:
        Object();
        void translate(const Eigen::Vector3f& point) override;
        void rotate(float angle, Eigen::Vector3f axis) override;
        void rotate(float angle) override;
        void move() override;
    protected:
        Eigen::Matrix4f T;
        Eigen::Vector3f center;
        Eigen::MatrixXf vertices;
    };

}

#endif //DRAW_MACHINE_MOVABLE_H
