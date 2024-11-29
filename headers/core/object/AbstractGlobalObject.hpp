#include "../headers/core/object/transform/AbstractTransform.hpp"
#include "../headers/core/object/localObject/AbstractLocalObject.hpp"

#include <memory>

#pragma once

class AbstractGlobalObject{

    private:
        unsigned long object_id;

    public:

        AbstractGlobalObject();

        unsigned long get_id();

                /**
         * Temporary getters
         * NOTE: THIS WILL BE REMOVED AND SUBSITUTED WITH A COMMAND PATTERN!
         */
        virtual std::shared_ptr<AbstractTransform> getTransform() const = 0;
        virtual std::shared_ptr<AbstractLocalObject> getObject() const = 0;

        operator std::string() const;
};