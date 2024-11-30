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

void Camera::look_at(glm::vec3 point){
    this->target = point;
}

void Camera::move_at(glm::vec3 location){
    this->position = location;
}

void Camera::set_up_vector(glm::vec3 up){
    this->up = up;
}