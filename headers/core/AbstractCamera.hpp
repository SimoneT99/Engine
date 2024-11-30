#include "../include/glm/glm.hpp"

#pragma once

class AbstractCamera{

    public:
        virtual glm::mat4x4 get_view_matrix() const = 0;
        virtual glm::mat4x4 get_projection_matrix() const = 0;
        
        /**
        * Base modifiers of the camera
        */
        virtual void look_at(glm::vec3 point) = 0;
        virtual void move_at(glm::vec3 location) = 0;
        virtual void set_up_vector(glm::vec3 up) = 0;
};