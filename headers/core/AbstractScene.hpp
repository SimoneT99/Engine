#include "../headers/core/AbstractCamera.hpp"
#include "../headers/core/object/AbstractGlobalObject.hpp"

#include <memory>

#pragma once

/**
 * BlackBoard class that will be used by both the engine (producer) and the pipeline (consumer)
 */

class AbstractScene{

    public:

        virtual std::shared_ptr<AbstractCamera> getCamera() const = 0;
        virtual bool hasCameraChanged() const = 0 ;
        virtual void clearCamera() = 0;

        virtual std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> getAllObjects() const = 0;
        virtual std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> getChangedObjects() const = 0;
        virtual void clearObjectChanges() = 0;

        virtual void addObject(std::shared_ptr<AbstractGlobalObject> object) = 0;

};