#include "../include/glm/glm.hpp"
#include "./AbstractLocalObject.hpp"
#include <tuple>
#include <memory>

#pragma once

/**
 * @brief An abstract definition of object builder to allow the use of dependency injection
 *  in the loader to allow mix-matching og different objects and loaders.
 */

class AbstractLocalObjectBuilder
{
public:
    virtual void clean() = 0;

    virtual void add_vertex(glm::vec4 vertex) = 0;
    virtual void add_face(glm::uvec3 face) = 0;
    virtual void add_normal(glm::vec3 normal) = 0;
    virtual void add_face_normal_mapping(std::tuple<unsigned int, unsigned int> face_normal_map) = 0;

    virtual std::unique_ptr<AbstractLocalObject> get_object() = 0;
};