#include "./cameraLense/AbstractLense.hpp"
#include "./cameraObject/AbstractCameraObject.hpp"

#include <memory>

#pragma once

/**
 * Abstract definition of a camera to put in the scene.
 */

class AbstractCamera{

    public:
        virtual std::shared_ptr<AbstractCameraObject> get_camera_object() const = 0;
        virtual std::shared_ptr<AbstractLense> get_lense() const = 0;

};