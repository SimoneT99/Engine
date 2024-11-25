/**
 * Object definition class to store an object with his data
 * This base form include only verticles and edges
 * 
 * An object has a list of nodes and a connection between them
 */

#include "AbstractObject.hpp"
#include "Vertex.hpp"
#include <map>
#include <utility>
#include <list>

#pragma once

class Object : AbstractObject{

    private:

        //require destruction!
        std::map<int, Vertex>* vertexes;

        std::list<std::tuple<int, int, int>>* faces;

    public:

        /**
         * Constructors
         */
        Object();

        /**
         * Expects an iterable collection of Vertexes
         */
        Object(const std::list<Vertex>& vertexes); //we do not need to modify it!

        /**
         * Expects an iterable collection of Vertexes and a list of edges:
         * @param vertexes: a list of vertexes, they will be indexed in the object based on the order in the given list
         * @param faces: a list of faces, it's been expected to be relative to the position in the list of the previous parameter, indexes
         *               should start from 1;
         */
        Object(const std::list<Vertex>& vertexes, const std::list<std::tuple<int, int, int>>& faces);
        
        /**
         * Copy Construtctor
         */
        Object(const Object& other);

        /**
         * Copy assignement operator with move semantic
         */
        Object& operator=(Object& other);

        /**
         * Destructor
         */
        ~Object();

        //needed to print out the vertex


};