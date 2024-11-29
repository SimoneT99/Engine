#include "../AbstractLocalObjectBuilder.hpp"
#include "./OptimizedObject.hpp"

#pragma once

/**
 * @brief Concrete implementation of the builder for the Optimized object.
 */

class OptimizedObjectBuilder : public AbstractLocalObjectBuilder
{

private:
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec3> normals;
    std::vector<glm::uvec3> faces;
    std::vector<std::tuple<unsigned int, unsigned int>> face_normal_mapping;

public:
    void clean() override;

    void add_vertex(glm::vec4 vertex) override;
    void add_face(glm::uvec3 face) override;
    void add_normal(glm::vec3 normal) override;
    void add_face_normal_mapping(std::tuple<unsigned int, unsigned int> face_normal_map) override;

    std::unique_ptr<AbstractLocalObject> get_object() override;
};