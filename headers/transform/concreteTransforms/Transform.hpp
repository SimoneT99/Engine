#include "../AbstractTransform.hpp"

#pragma once

class Transform : public AbstractTransform
{

private:
    glm::mat4x4 rotation_matrix;
    glm::mat4x4 scaling_matrix;
    glm::mat4x4 translation_matrix;

    std::string print_mat4x4(const glm::mat4x4& matrix) const;

protected:
    std::string print_translation() const override;
    std::string print_rotation() const override;
    std::string print_scaling() const override;
    std::string print_model_matrix() const override;

public:
    Transform();

    /**
     * rule of the three
     */
    Transform(const Transform &other);
    ~Transform();
    Transform &operator=(Transform &other);

    void translate(float x, float y, float z) override;
    void set_translation(float x, float y, float z) override;
    void reset_translation() override;

    void rotate(const glm::quat &rotation) override;
    void set_rotation(const glm::quat &rotation) override;
    void reset_rotation() override;

    void scale(float x, float y, float z) override;
    void set_scale(float x, float y, float z) override;
    void reset_scale() override;

    glm::mat4x4* get_model_matrix_reference() const override;
    glm::mat4x4 get_model_matrix_direct() const override;

    std::unique_ptr<AbstractTransform> clone() const override;
};