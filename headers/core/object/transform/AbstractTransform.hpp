/**
 * Abstract definition of the transform class, 
 */

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/quaternion.hpp"
#include <memory>
#include <string>
#include <sstream>

#pragma once

class AbstractTransform{

    protected:
        virtual std::string print_translation() const = 0;
        virtual std::string print_rotation() const = 0;
        virtual std::string print_scaling() const = 0;
        virtual std::string print_model_matrix() const = 0;

    public:
        /**
         * Translation methods
         */
        virtual void translate(float x, float y, float z) = 0;
        virtual void set_translation(float x, float y, float z) = 0;
        virtual void reset_translation() = 0;

        /**
         * Rotation methods
         */
        virtual void rotate(const glm::quat& rotation) = 0;
        virtual void set_rotation(const glm::quat& rotation) = 0;
        virtual void reset_rotation() = 0;

        /**
         * Scaling methods
         */
        virtual void scale(float x, float y, float z) = 0;
        virtual void set_scale(float x, float y, float z) = 0;
        virtual void reset_scale() = 0;

        /**
         * Current Transform matrix
         */
        virtual glm::mat4x4* get_model_matrix_reference() const = 0;
        virtual glm::mat4x4 get_model_matrix_direct() const = 0;

        /**
         * Cloning to allow for deep copy indipendently of the implementation
         * -> violation of OOP principles...
         */
        virtual std::unique_ptr<AbstractTransform> clone() const = 0;

        /**
         * String conversion for printing
         */
        operator std::string() const;
};