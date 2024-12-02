#include "headers/core/camera/cameraObject/concreteCamera/CameraObject.hpp"

glm::mat4x4 Camera::get_view_matrix() const
{
    return glm::lookAt(this->position, this->target, this->up);
}

void Camera::look_at(glm::vec3 point)
{
    this->target = point;
}

void Camera::move_at(glm::vec3 location)
{
    this->position = location;
}

void Camera::set_up_vector(glm::vec3 up)
{
    this->up = up;
}

inline bool vectorIsNull(glm::vec3 vector)
{
    return std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z);
}

void Camera::set_camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up)
{
    if (!vectorIsNull(position))
    {
        this->move_at(position);
    }
    if (!vectorIsNull(look_at))
    {
        this->look_at(look_at);
    }
    if (!vectorIsNull(up))
    {
        this->set_up_vector(up);
    }
}

glm::vec3 Camera::get_position() const
{
    return this->position;
}

glm::vec3 Camera::get_looking_direction() const
{
    return this->target;
}
glm::vec3 Camera::get_up_vector() const
{
    return this->up;
}