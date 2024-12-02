/**
 * TODO: a camera is just another object in the scene... it's a subclass of abstractObject, but without the local object model...
 */

#include "../AbstractCameraObject.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

#pragma once

class Camera : public AbstractCameraObject
{

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    /**
     * Backed data
     */

    bool changed_view;
    bool changed_perspective;
    glm::mat4x4 current_view_matrix;
    glm::mat4x4 current_perspective_matrix;

    inline bool vectorIsNull(glm::vec3 vector);

public:
    Camera(
        glm::vec3 position,
        glm::vec3 target,
        glm::vec3 up)
        : position(position),
          target(target),
          up(up)
    {
    }

    glm::mat4x4 get_view_matrix() const override;

    void look_at(glm::vec3 point);
    void move_at(glm::vec3 location);
    void set_up_vector(glm::vec3 up);
    void set_camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up);

    glm::vec3 get_position() const override;
    glm::vec3 get_looking_direction() const override;
    glm::vec3 get_up_vector() const override;
};