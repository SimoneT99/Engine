#include "../headers/core/object/localObject/AbstractLocalObject.hpp"

AbstractLocalObject::operator std::string() const{

    std::ostringstream oss;

    oss << "Vertexes:\n";
    oss << this->print_vertexes();
    oss << "Normals:\n";
    oss << this->print_normals();
    oss << "Faces:\n";
    oss << this->print_faces();
    oss << "Face-Normal mapping:\n";
    oss << this->print_face_normal_mapping();

    // Return the constructed string
    return oss.str();

}