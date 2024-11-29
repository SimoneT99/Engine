#pragma once

/**
 * Container class, no logic is applied here
 */
class OpenGLObjectInformations
{

    unsigned int vao;
    unsigned int vertex_buffer_id;
    unsigned int index_buffer_id;
    unsigned int model_transform_buffer_id;

    /**
     * Other data
     */
    int number_of_verticles;
    int number_of_faces;

public:

    OpenGLObjectInformations(
        unsigned int vao,
        unsigned int vertex_buffer_id,
        unsigned int index_buffer_id,
        unsigned int model_transform_buffer_id,
        int number_of_verticles,
        int number_of_faces) : vao(vao),
                               vertex_buffer_id(vertex_buffer_id),
                               index_buffer_id(index_buffer_id),
                               model_transform_buffer_id(model_transform_buffer_id),
                               number_of_verticles(number_of_verticles),
                               number_of_faces(number_of_faces) {};

    unsigned int get_vao() const;
    unsigned int get_vertex_buffer_id() const;
    unsigned int get_index_buffer_id() const;
    unsigned int get_model_transform_buffer() const;
    int get_number_of_verticles() const;
    int get_number_of_faces() const;
};