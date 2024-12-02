#include "../include/glm/glm.hpp"
#include <memory>

#pragma once

class AbstractCameraObject{

    public:
        /**
         * Bundled camera configuration
         * @param position: the position in which the camera will be placed
         * @param look_at: the directon in which the camera will be pointed at
         * @param up: the direction in wich the camera will have its top pointed to;
         * NOTE: A better solution to bundle actions is welcome...
         */
        virtual void set_camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up) = 0;

        virtual void look_at(glm::vec3 point) = 0;
        virtual void move_at(glm::vec3 location) = 0;
        virtual void set_up_vector(glm::vec3 up) = 0;

        /**
         * Getters
         */

        virtual glm::mat4x4 get_view_matrix() const = 0;

        virtual glm::vec3 get_position() const = 0;
        virtual glm::vec3 get_looking_direction() const = 0;
        virtual glm::vec3 get_up_vector() const = 0;
};