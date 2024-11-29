#include "../headers/core/object/AbstractGlobalObject.hpp"

AbstractGlobalObject::AbstractGlobalObject(){
    this->object_id = object_id++;
}

unsigned long AbstractGlobalObject::get_id(){
    return this->object_id;
}

AbstractGlobalObject::operator std::string() const{

    std::ostringstream oss;

    oss << "Object:\n";
    oss << static_cast<std::string>(*(this->getObject())) << std::endl;
    oss << "Transform:\n";
    oss << static_cast<std::string>(*(this->getTransform())) << std::endl;

    // Return the constructed string
    return oss.str();

}

static unsigned long object_id = 1;