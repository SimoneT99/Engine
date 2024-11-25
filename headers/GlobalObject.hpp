/**
 * Global object class
 * It represents an object in the scene
 */
#include "./object/AbstractObject.hpp"
#include "./transform/AbstractTransform.hpp"

#pragma once

class GlobalObject{

    private:

        /**
         * TODO smart pointer could be a useful safety net, since we want each global object
         * to be associated with only one transform and one object, if we want to mantain the
         * dependency injection we need to make sure that possesion of both is only of the given global object
         * 
         * We assure that both are unique by using a deep copy;
         */

        AbstractObject* local_object;     //The local object information
        AbstractTransform* transform;     //The information that specifies the position, rotation and scaling of the object
        bool loaded_in_pipeline; //Binary flag to check if the object is already loaded in the pipeline

    public:

        GlobalObject(const AbstractObject& object, const AbstractTransform& transform);

        /**
         * rule of the three
         */
        GlobalObject(const GlobalObject& other);
        ~GlobalObject();
        GlobalObject& operator=(GlobalObject& other);

        /**
         * Temporary getters
         * NOTE: THIS WILL BE REMOVED AND SUBSITUTED WITH A COMMAND PATTERN!
         */
        AbstractTransform* getTransform() const;
        AbstractObject* getObject() const;


        operator std::string() const;
};