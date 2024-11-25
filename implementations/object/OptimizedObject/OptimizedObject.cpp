#include "../headers/object/OptimizedObject/OptimizedObject.hpp"

/**
 * Abstract object override
 */

std::vector<glm::vec4> OptimizedObject::get_vertexes() const
{
    return this->vertexes;
}

std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> OptimizedObject::get_faces() const
{
    return this->faces;
}

std::vector<glm::vec3> OptimizedObject::get_normals() const
{
    return this->normals;
}

std::vector<std::tuple<unsigned int, unsigned int>> OptimizedObject::get_faces_normal_mapping() const
{
    return this->face_normal_mapping;
}

glm::vec4 OptimizedObject::get_vertex_at(int location) const
{
    return this->vertexes.at(location);
}

glm::vec3 OptimizedObject::get_normal_at(int location) const
{
    return this->normals.at(location);
}

std::tuple<unsigned int, unsigned int, unsigned int> OptimizedObject::get_face_at(int location) const
{
    return this->faces.at(location);
}

std::unique_ptr<AbstractObject> OptimizedObject::clone() const
{
    AbstractObject* object = (AbstractObject *) new OptimizedObject(*this);
    return std::unique_ptr<AbstractObject>(object);
}

std::string OptimizedObject::print_vertexes() const{
    std::ostringstream oss;
    for (const auto& vertex : vertexes) {
        oss << "  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ", " << vertex.w << ")\n";
    }
    return oss.str();
}

std::string OptimizedObject::print_faces() const{
    std::ostringstream oss;
    for (const auto& face : faces) {
        oss << "  (" << std::get<0>(face) << ", " << std::get<1>(face) << ", " << std::get<2>(face) << ")\n";
    }
    return oss.str();
}

std::string OptimizedObject::print_normals() const{
    std::ostringstream oss;
    for (const auto& normal : normals) {
        oss << "  (" << normal.x << ", " << normal.y << ", " << normal.z << ")\n";
    }
    return oss.str();
}

std::string OptimizedObject::print_face_normal_mapping() const{
    std::ostringstream oss;
    for (const auto& mapping : face_normal_mapping) {
        oss << "  (" << std::get<0>(mapping) << ", " << std::get<1>(mapping) << ")\n";
    }
    return oss.str();
}
