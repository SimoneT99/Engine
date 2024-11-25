#include "headers\legacy\Vertex.hpp"

Vertex::Vertex(float x_position, float y_position, float z_position){
    this->x_position = x_position;
    this->y_position = y_position;
    this->z_position = z_position;
    }

//setters
void Vertex::set_x_position(float x_position){
    this->x_position = x_position;
}

void Vertex::set_y_position(float y_position){
    this->y_position = y_position;
}

void Vertex::set_z_position(float z_position){
    this->z_position = z_position;
}


//getters
float Vertex::get_x_position() const{
    return x_position;
}

float Vertex::get_y_position() const{
    return y_position;
}

float Vertex::get_z_position() const{
    return z_position;
}


//string operator
Vertex::operator std::string() const{
            return "x = " + std::to_string(this->get_x_position()) + " y = " + std::to_string(this->get_y_position()) + " z = " + std::to_string(this->get_z_position());
}