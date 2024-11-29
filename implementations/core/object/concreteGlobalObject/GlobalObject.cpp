#include "../headers/core/object/concreteGlobalObject/GlobalObject.hpp"

GlobalObject::GlobalObject(const AbstractLocalObject& object, const AbstractTransform& transform){
    this->local_object = std::move(object.clone());
    this->object_transform = std::move(transform.clone());
}

std::shared_ptr<AbstractTransform> GlobalObject::getTransform() const{
    return this->object_transform;
};

std::shared_ptr<AbstractLocalObject> GlobalObject::getObject() const{
    return this->local_object;
};