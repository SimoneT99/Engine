#include "../headers/core/concreteCamera/Camera.hpp"

glm::mat4x4 Camera::get_view_matrix() const{
    return glm::lookAt(this->position, this->target, this->up);
}
    

glm::mat4x4 Camera::get_projection_matrix() const{
    return glm::perspective(
            glm::radians(this->vertical_fov),
            this->aspect_ratio,
            this->near_plane,
            this->far_plane
        );
}