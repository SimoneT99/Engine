#include "../include/glm/glm.hpp"
#include <vector>
#include <memory>
#include <string>
#include <sstream>

#pragma once

/**
 * Pure abstract class defining an object in the engine
 * Represents an object with faces and normals;
 * 
 * NOTE: The data is copied and then passed as value, this is inefficient if the object become very
 *          big. A better idea would be to just pass a constant reference so no copy would be needed,
 *          but we lose the ability to modify the object dynamically...
 */

class AbstractLocalObject{

    protected:
        /**
         * I know... we should bind also the way the single stuff is presented but for now
         * this is good enough
         */
        virtual std::string print_vertexes() const = 0;
        virtual std::string print_faces() const = 0;
        virtual std::string print_normals() const = 0;
        virtual std::string print_face_normal_mapping() const = 0;

    public:

        virtual std::vector<glm::vec4> get_vertexes() const = 0;
        virtual std::vector<glm::uvec3> get_faces() const = 0;
        virtual std::vector<glm::vec3> get_normals() const = 0;
        virtual std::vector<std::tuple<unsigned int, unsigned int>> get_faces_normal_mapping() const = 0;

        virtual glm::vec4 get_vertex_at(int location) const = 0;
        virtual glm::vec3 get_normal_at(int location) const = 0;
        virtual glm::uvec3 get_face_at(int location) const = 0;

        virtual std::unique_ptr<AbstractLocalObject> clone() const = 0;

        operator std::string() const;
};