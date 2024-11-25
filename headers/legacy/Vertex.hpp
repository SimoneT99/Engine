/**
 * Vertex class used to store vertex informations
 */

#include <string>

#pragma once

class Vertex{

    private:
        float x_position;
        float y_position;
        float z_position;

    public:
        Vertex(float x_position,
               float y_position,
               float z_position);

        //setters
        void set_x_position(float x_position);
        void set_y_position(float y_position);
        void set_z_position(float z_position);

        //getters
        float get_x_position() const;
        float get_y_position() const;
        float get_z_position() const;

        //needed to print out the vertex
        operator std::string() const;

};