#include "../headers/core/object/transform/concreteTransform/Transform.hpp"

Transform::Transform()
{
    this->translation_matrix = glm::mat4x4(1.0f); //NOTE: Stupid... we do not need a whole matrix for this...
    this->rotation_matrix = glm::mat4x4(1.0f);
    this->scaling_matrix = glm::mat4x4(1.0f);  //NOTE: Stupid again... we do not need a whole matrix for this either...
}

Transform::Transform(const Transform &other)
{
    this->translation_matrix = other.translation_matrix;
    this->rotation_matrix = other.rotation_matrix;
    this->scaling_matrix = other.scaling_matrix;
}

Transform::~Transform()
{
    /**
     * not needed since we do not use pointers for the matrixes
     */
}

Transform &Transform::operator=(Transform &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->translation_matrix = other.translation_matrix;
    this->rotation_matrix = other.rotation_matrix;
    this->scaling_matrix = other.scaling_matrix;

    return *this;
}

/**
 * Translation
 */

void Transform::translate(float x, float y, float z)
{

    glm::mat4x4 translation_matrix = glm::mat4x4( // using the stack for efficiency
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1);

    //this->translation_matrix = glm::matrixCompMult(translation_matrix, this->translation_matrix);
    this->translation_matrix = translation_matrix * this->translation_matrix;

}

void Transform::set_translation(float x, float y, float z)
{
    this->translation_matrix = glm::mat4x4( // using the stack for efficiency
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1);
}

void Transform::reset_translation()
{
    this->translation_matrix = glm::mat4x4(1.0f);
}

/**
 * Rotation
 */

void Transform::rotate(const glm::quat &rotation)
{

    float w = rotation.w;
    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;

    /**
     * Might be source of errors if not done correctly
     */
    glm::mat4x4 rotation_matrix = glm::mat4x4(
        1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, 0,
        2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x, 0,
        2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y, 0,
        0, 0, 0, 1);

    //this->rotation_matrix = glm::matrixCompMult(rotation_matrix, this->translation_matrix);
    this->rotation_matrix = rotation_matrix * this->rotation_matrix;
}

void Transform::set_rotation(const glm::quat &rotation)
{

    float w = rotation.w;
    float x = rotation.x;
    float y = rotation.y;
    float z = rotation.z;

    this->rotation_matrix = glm::mat4x4(
        1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, 0,
        2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x, 0,
        2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y, 0,
        0, 0, 0, 1);
}

void Transform::reset_rotation()
{
    this->translation_matrix = glm::mat4x4(1.0f);
}

/**
 * Scaling
 */

void Transform::scale(float x, float y, float z)
{

    glm::mat4x4 scaling_matrix = glm::mat4x4( // using the stack for efficiency
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1);

    //this->scaling_matrix = glm::matrixCompMult(translation_matrix, this->translation_matrix);
    this->scaling_matrix = scaling_matrix * this->scaling_matrix;

}

void Transform::set_scale(float x, float y, float z)
{

    this->scaling_matrix = glm::mat4x4( // using the stack for efficiency
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1);
}

void Transform::reset_scale()
{
    this->scaling_matrix = glm::mat4x4(1.0f);
}

glm::mat4x4 *Transform::get_model_matrix_reference() const
{

    glm::mat4x4 *output = new glm::mat4x4();
    // hoping it implements the move semantic
    //*output = glm::matrixCompMult(this->translation_matrix, glm::matrixCompMult(this->scaling_matrix, this->rotation_matrix));
    *output = this->translation_matrix * this->scaling_matrix * this->rotation_matrix;
    // Possible memory leak!
    return output;
}

glm::mat4x4 Transform::get_model_matrix_direct() const
{

    // direct transfer
    return this->rotation_matrix * this->scaling_matrix * this->translation_matrix;
}

std::unique_ptr<AbstractTransform> Transform::clone() const
{

    // Fuck this bullshit lol
    AbstractTransform *transform = (AbstractTransform *)new Transform(*this);
    return std::unique_ptr<AbstractTransform>(transform);
}

/**
 * Printing methods
 */
std::string Transform::print_mat4x4(const glm::mat4x4 &matrix) const
{
    std::ostringstream oss;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            oss << matrix[i][j];
            if (j < 3)
                oss << ", "; // Separatore tra gli elementi di una riga
        }
        if (i < 3)
            oss << "\n"; // Vai a capo tra le righe
    }
    return oss.str();
}

std::string Transform::print_translation() const
{
    return this->print_mat4x4(this->translation_matrix);
}

std::string Transform::print_rotation() const
{
    return this->print_mat4x4(this->rotation_matrix);
}
std::string Transform::print_scaling() const
{
    return this->print_mat4x4(this->scaling_matrix);
}
std::string Transform::print_model_matrix() const
{
    return this->print_mat4x4(this->get_model_matrix_direct());
}