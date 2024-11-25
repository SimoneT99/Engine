#include "../headers/object/OptimizedObject/OptimizedObjectBuilder.hpp"

void OptimizedObjectBuilder::clean()
{
    this->vertexes.clear();
    this->normals.clear();
    this->faces.clear();
    this->face_normal_mapping.clear();
}

void OptimizedObjectBuilder::add_vertex(glm::vec4 vertex)
{
    this->vertexes.push_back(vertex);
}

void OptimizedObjectBuilder::add_face(std::tuple<unsigned int, unsigned int, unsigned int> face)
{
    this->faces.push_back(face);
}

void OptimizedObjectBuilder::add_normal(glm::vec3 normal)
{
    this->normals.push_back(normal);
}

void OptimizedObjectBuilder::add_face_normal_mapping(std::tuple<unsigned int, unsigned int> face_normal_map)
{
    this->face_normal_mapping.push_back(face_normal_map);
}

std::unique_ptr<AbstractObject> OptimizedObjectBuilder::get_object()
{
    return std::make_unique<OptimizedObject>(
        this->vertexes,
        this->normals,
        this->faces,
        this->face_normal_mapping
    );
}