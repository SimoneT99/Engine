/**
 * Object definition class to store an object with his data
 * This base form include only verticles and edges
 *
 * An object has a list of nodes and a connection between them
 */

#include "../AbstractLocalObject.hpp"
#include <map>
#include <utility>
#include <list>
#include <string>

#pragma once

class OptimizedObject : public AbstractLocalObject
{

private:
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec3> normals;
    std::vector<glm::uvec3> faces;

    std::vector<std::tuple<unsigned int, unsigned int>> face_normal_mapping;


protected:

    std::string print_vertexes() const override;
    std::string print_faces() const override;
    std::string print_normals() const override;
    std::string print_face_normal_mapping() const override;

public:
    /**
     * Constructors, deconstructors and other needed stuff
     */

    OptimizedObject(
        const std::vector<glm::vec4> &vertexes,
        const std::vector<glm::vec3> &normals,
        const std::vector<glm::uvec3> &faces,
        const std::vector<std::tuple<unsigned int, unsigned int>> &face_normal_mapping)
        : vertexes(vertexes),
          normals(normals),
          faces(faces),
          face_normal_mapping(face_normal_mapping) {}

    /**
     * Abstract object override
     */

    std::vector<glm::vec4> get_vertexes() const override;
    std::vector<glm::uvec3> get_faces() const override;
    std::vector<glm::vec3> get_normals() const override;
    std::vector<std::tuple<unsigned int, unsigned int>> get_faces_normal_mapping() const override;

    glm::vec4 get_vertex_at(int location) const override;
    glm::vec3 get_normal_at(int location) const override;
    glm::uvec3 get_face_at(int location) const override;

    std::unique_ptr<AbstractLocalObject> clone() const override;
};