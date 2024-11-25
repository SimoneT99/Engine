/**
 * TODO: a camera is just another object in the scene... it's a subclass of abstractObject, but without the local object model...
 */

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

#pragma once

class Camera
{

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float vertical_fov;
    float aspect_ratio;
    float near_plane;
    float far_plane;

    /**
     * Backed data
     */

    bool changed_view;
    bool changed_perspective;
    glm::mat4x4 current_view_matrix;
    glm::mat4x4 current_perspective_matrix;

public:

    Camera(
        glm::vec3 position,
        glm::vec3 target,
        glm::vec3 up,
        float vertical_fov,
        float aspect_ratio,
        float near_plane,
        float far_plane
        )
        : position(position),
          target(target),
          up(up),
          vertical_fov(vertical_fov),
          aspect_ratio(aspect_ratio),
          near_plane(near_plane),
          far_plane(far_plane),
          changed_view(true),
          changed_perspective(true)
    {
    }

    glm::mat4x4 get_view_matrix();
    glm::mat4x4 get_projection_matrix();
};