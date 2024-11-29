/**
 * Global object class
 * It represents an object in the scene
 */
#include "../headers/core/object/AbstractGlobalObject.hpp"

#pragma once

class GlobalObject : public AbstractGlobalObject{

    private:
        std::shared_ptr<AbstractLocalObject> local_object;
        std::shared_ptr<AbstractTransform> object_transform;

    public:

        GlobalObject(const AbstractLocalObject& object, const AbstractTransform& transform);
        GlobalObject(std::shared_ptr<AbstractLocalObject> object, std::shared_ptr<AbstractTransform> transform)
        : local_object(std::move(object)), 
          object_transform(std::move(transform))
        {};
        
        std::shared_ptr<AbstractTransform> getTransform() const override;
        std::shared_ptr<AbstractLocalObject> getObject() const override;

        operator std::string() const;
};