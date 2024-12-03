#include "./AbstractCameraObject.hpp"
#include <memory>

#pragma once

class AbstractCameraObjectProxy : public AbstractCameraObject {

    protected:
        std::shared_ptr<AbstractCameraObject> abstractCamera;

    public:
        AbstractCameraObjectProxy(std::shared_ptr<AbstractCameraObject> abstractCamera) :
        abstractCamera(std::move(abstractCamera)){}
};