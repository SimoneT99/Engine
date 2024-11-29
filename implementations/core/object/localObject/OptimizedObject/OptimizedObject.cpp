#include "../headers/core/object/localObject/OptimizedObject/OptimizedObject.hpp"

/**
 * Abstract object override
 */

std::vector<glm::vec4> OptimizedObject::get_vertexes() const
{
    return this->vertexes;
}

std::vector<glm::uvec3> OptimizedObject::get_faces() const
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

glm::uvec3 OptimizedObject::get_face_at(int location) const
{
    return this->faces.at(location);
}

std::unique_ptr<AbstractLocalObject> OptimizedObject::clone() const
{
    AbstractLocalObject* object = (AbstractLocalObject *) new OptimizedObject(*this);
    return std::unique_ptr<AbstractLocalObject>(object);
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
        oss << "  (" << face.x << ", " << face.y << ", " << face.z << ")\n";
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
