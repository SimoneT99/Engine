#include "../headers/pipeline/concreteRenderer/BaseOpenGLRenderer/OpenGlObjectInformations.hpp"

unsigned int OpenGLObjectInformations::get_vao() const
{
    return this->vao;
}

unsigned int OpenGLObjectInformations::get_vertex_buffer_id() const
{
    return this->vertex_buffer_id;
}

unsigned int OpenGLObjectInformations::get_index_buffer_id() const
{
    return this->index_buffer_id;
}
unsigned int OpenGLObjectInformations::get_model_transform_buffer() const
{
    return this->model_transform_buffer_id;
}
int OpenGLObjectInformations::get_number_of_verticles() const
{
    return this->number_of_verticles;
}
int OpenGLObjectInformations::get_number_of_faces() const
{
    return this->number_of_faces;
}