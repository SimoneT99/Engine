#include "../include/glm/glm.hpp"

#pragma once

class AbstractCamera{

    public:
        virtual glm::mat4x4 get_view_matrix() const = 0;
        virtual glm::mat4x4 get_projection_matrix() const = 0;
};