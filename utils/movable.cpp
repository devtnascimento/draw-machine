#include <utils/movable.h>

using namespace std;

movable::Object::Object() = default;

void movable::Object::translate(const Eigen::Vector3f& point) {
    Eigen::Affine3f transform(this->T);
    Eigen::Translation3f translation(point);
    transform *= translation;
    this->T = transform.matrix();
}

void movable::Object::rotate(float angle, Eigen::Vector3f axis) {
    angle = static_cast<float>(angle * M_PI / 180.0f);

    Eigen::Quaternionf rotation = Eigen::Quaternionf(Eigen::AngleAxisf(angle, axis));

    cout << "quaternion from eigen: " << endl;
    cout << rotation << endl << endl;
    Eigen::Affine3f transform(this->T);

    cout << "transform from eigen: " << endl;
    cout << transform.matrix() << endl << endl;

    transform.rotate(rotation);

    this->T = transform.matrix();

    cout << "rotation from eigen: " << endl;

    cout << this->T << endl;

}

void movable::Object::rotate(float angle) {
    angle = static_cast<float>(angle * M_PI / 180.0f);

    Eigen::Quaternionf rotation = Eigen::Quaternionf(Eigen::AngleAxisf(angle, this->center.normalized()));

    cout << "quaternion from eigen: " << endl;
    cout << rotation << endl << endl;
    Eigen::Affine3f transform(this->T);

    cout << "transform from eigen: " << endl;
    cout << transform.matrix() << endl << endl;

    transform.rotate(rotation);

    this->T = transform.matrix();

    cout << "rotation from eigen: " << endl;

    cout << this->T << endl;
}


void movable::Object::move() {
    for (int i=0; i < this->vertices.rows(); i++){
        Eigen::Vector4f new_vertex;
        new_vertex = this->T * Eigen::Vector4f(this->vertices(i, 0),
                                                this->vertices(i, 1),
                                                this->vertices(i, 2),
                                                1.0f
        );
        this->vertices(i, 0) = new_vertex[0];
        this->vertices(i, 1) = new_vertex[1];
        this->vertices(i, 2) = new_vertex[2];
        this->vertices = this->vertices.normalized();
    }
}




