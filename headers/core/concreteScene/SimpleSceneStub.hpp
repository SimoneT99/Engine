#include "../headers/core/AbstractScene.hpp"

#pragma once

/**
    @brief Stub concrete class implementation
    @note This should not be used in any final product
*/

class SimpleSceneStub : public AbstractScene{

    private:

        std::shared_ptr<AbstractCamera> scene_camera;
        std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> global_objects;

    public:

        SimpleSceneStub(
            std::shared_ptr<AbstractCamera> scene_camera
        ) : scene_camera(scene_camera){
        }

        std::shared_ptr<AbstractCamera> getCamera() const override;
        bool hasCameraChanged() const override;
        void clearCamera() override;

        std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> getAllObjects() const;
        std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> getChangedObjects() const override;
        void clearObjectChanges() override;

        void addObject(std::shared_ptr<AbstractGlobalObject> object) override;

};