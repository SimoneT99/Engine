#include "../AbstractObjectBuilder.hpp"
#include "OptimizedObject.hpp"

/**
 * @brief Concrete implementation of the builder for the Optimized object.
 */

class OptimizedObjectBuilder : public AbstractObjectBuilder
{

private:
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec3> normals;
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> faces;
    std::vector<std::tuple<unsigned int, unsigned int>> face_normal_mapping;

public:
    void clean() override;

    void add_vertex(glm::vec4 vertex) override;
    void add_face(std::tuple<unsigned int, unsigned int, unsigned int> face) override;
    void add_normal(glm::vec3 normal) override;
    void add_face_normal_mapping(std::tuple<unsigned int, unsigned int> face_normal_map) override;

    std::unique_ptr<AbstractObject> get_object() override;
};