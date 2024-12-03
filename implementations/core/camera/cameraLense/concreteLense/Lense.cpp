#include "../headers/core/camera/cameraLense/concreteLense/Lense.hpp"

glm::mat4x4 Lense::get_projection_matrix() const{
    return glm::perspective(
            glm::radians(this->vertical_fov),
            this->aspect_ratio,
            this->near_plane,
            this->far_plane
        );
}

void Lense::set_vertical_fov(float vertical_fov){
    this->vertical_fov = vertical_fov;
}
void Lense::set_aspect_ratio(float aspect_ratio){
    this->aspect_ratio = aspect_ratio;
}
void Lense::set_near_plane(float near_plane){
    this->near_plane = near_plane;
}
void Lense::set_far_plane(float far_plane){
    this->far_plane = far_plane;
}

void Lense::bundled_change(float vertical_fov, float aspect_ratio, float near_plane, float far_plane){
    if(vertical_fov != NULL){
        this->vertical_fov = vertical_fov;
    }
    if(aspect_ratio != NULL){
        this->aspect_ratio = aspect_ratio;
    }
    if(near_plane != NULL){
        this->near_plane = near_plane;
    }
    if(far_plane != NULL){
        this->far_plane = far_plane;
    }
}

float Lense::get_vertical_fov() const{
    return this->vertical_fov;
}

float Lense::get_aspect_ratio() const{
    return this->aspect_ratio;
}

float Lense::get_near_plane() const{
    return this->near_plane;
}
float Lense::get_far_plane() const{
    return this->far_plane;
}