#include "../headers/GlobalObject.hpp"

GlobalObject::GlobalObject(const AbstractObject& object, const AbstractTransform& transform){
    this->local_object = object.clone().release();
    this->transform = transform.clone().release();
}

GlobalObject::GlobalObject(const GlobalObject& other){
    this->local_object = other.local_object->clone().release();
    this->transform = other.transform->clone().release();
    this->loaded_in_pipeline = other.loaded_in_pipeline;
}

GlobalObject::~GlobalObject(){
    delete(this->local_object);
    delete(this->transform);
}

GlobalObject& GlobalObject::operator=(GlobalObject& other){
    
    if(this == &other){
        return *this;
    }

    delete(this->local_object);
    delete(this->transform);

    this->local_object = other.local_object;
    this->transform = other.transform;
    this->loaded_in_pipeline = other.loaded_in_pipeline;

    other.local_object = nullptr;
    other.transform = nullptr;

    return *this;
}

GlobalObject::operator std::string() const{

    std::ostringstream oss;

    oss << "Object:\n";
    oss << static_cast<std::string>(*(this->local_object)) << std::endl;
    oss << "Transform:\n";
    oss << static_cast<std::string>(*(this->transform)) << std::endl;

    // Return the constructed string
    return oss.str();

}

AbstractTransform* GlobalObject::getTransform() const {
    return this->transform;
}

AbstractObject* GlobalObject::getObject() const {
    return this->local_object;
}