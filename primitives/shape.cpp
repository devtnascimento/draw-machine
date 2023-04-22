#include <primitives/shape.h>

using namespace std;


primitive::Shape::Shape(const Vertices& vertices, const Indices& indices,
        const string& vs_path, const string& fs_path) {

    this->vertices = vertices;
    this->size = static_cast<GLsizeiptr>(vertices.size()*sizeof(float));
    this->vs_path = vs_path;
    this->fs_path = fs_path;
    this->start_index = 0;
    this->context = glfwGetCurrentContext();
    this->stride = static_cast<GLsizei>(this->vertices.cols()*sizeof(float));
    this->indices = indices;
    this->i_size = static_cast<GLsizeiptr>(indices.size()*sizeof(int));
    this->texture1 = new utils::Texture("container", GL_RGB);
    this->texture2 = new utils::Texture("awesomeface", GL_RGBA, true);
    this->T = Transform::Identity();
    this->center = this->vertices.block(0, 0, this->vertices.rows(), 3).colwise().mean();
}

void primitive::Shape::build () {

    this->getShadersSources();
    this->compileShaders();
    this->linkProgram();

    cout << this->T << endl;
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->size, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->i_size, this->indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->stride, nullptr);
    glEnableVertexAttribArray(0);

    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, this->stride, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(this->program);
    glUniform1i(glGetUniformLocation(this->program, "texture1"), 0);
    glUniform1i(glGetUniformLocation(this->program, "texture2"), 1);
}

void primitive::Shape::draw() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture1->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->texture2->id);

    this->translate(Eigen::Vector3f(0.5f, -0.5f, 0.0f));
    float angle = 45.0f;
    this->rotate(angle, Eigen::Vector3f(0.0f, 0.0f, 1.0f));

    glUseProgram(this->program);
    GLint transformLoc = glGetUniformLocation(this->program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, this->T.data());
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void primitive::Shape::translate(const Eigen::Vector3f& point) {

    Eigen::Affine3f transform(this->T);
    Eigen::Translation3f translation(point);
    transform *= translation;
    this->T = transform.matrix();
}

void primitive::Shape::rotate(float angle, Eigen::Vector3f axis) {

    angle = static_cast<float>(angle * M_PI / 180.0f);
    Eigen::Quaternionf rotation = Eigen::Quaternionf(Eigen::AngleAxisf(angle, axis));
    Eigen::Affine3f transform(this->T);
    transform.rotate(rotation);
    this->T = transform.matrix();
}

void primitive::Shape::rotate(float angle) {

    angle = static_cast<float>(angle * M_PI / 180.0f);
    auto rotation = Eigen::Quaternionf(Eigen::AngleAxisf(angle, this->center.normalized()));
    Eigen::Affine3f transform(this->T);
    transform.rotate(rotation);
    this->T = transform.matrix();
}

void primitive::Shape::move() {

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
