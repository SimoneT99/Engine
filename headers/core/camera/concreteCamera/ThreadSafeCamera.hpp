#include "../AbstractCamera.hpp"
#include "../cameraObject/AbstractCameraObject.hpp"
#include "../cameraLense/AbstractLense.hpp"
#include "../headers/core/camera/cameraLense/concreteProxy/LenseThreadSafetyProxy.hpp"
#include "../headers/core/camera/cameraObject/concreteProxy/CameraObjectThreadSafetyProxy.hpp"

#pragma once

class ThreadSafeCamera : public AbstractCamera{

    std::shared_ptr<AbstractCameraObject> abstract_camera_object;
    std::shared_ptr<AbstractLense> abstract_lense;

    public:
        ThreadSafeCamera(
            std::shared_ptr<AbstractCameraObject> abstractCameraObject,
            std::shared_ptr<AbstractLense> abstractLense) : 
            abstract_camera_object(std::make_shared<CameraObjectThreadSafetyProxy>(abstractCameraObject)),
            abstract_lense(std::make_shared<LenseThreadSafetyProxy>(abstractLense)){
            }

        std::shared_ptr<AbstractCameraObject> get_camera_object() const override;
        std::shared_ptr<AbstractLense> get_lense() const override;
};