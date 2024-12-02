#include "headers/core/camera/concreteCamera/ThreadSafeCamera.hpp"

std::shared_ptr<AbstractCameraObject> ThreadSafeCamera::get_camera_object() const {
    return this->abstract_camera_object;
}

std::shared_ptr<AbstractLense> ThreadSafeCamera::get_lense() const {
    return this->abstract_lense;
}