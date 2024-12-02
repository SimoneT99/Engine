#include "../include/glm/glm.hpp"
class AbstractLense{
    public:
    virtual glm::mat4x4 get_projection_matrix() const = 0;

    virtual void set_vertical_fov(float fov) = 0;
    virtual void set_aspect_ratio(float aspect_ratio) = 0;
    virtual void set_near_plane(float near_plane) = 0;
    virtual void set_far_plane(float far_plane) = 0;
    virtual void bundled_change(float fov, float aspect_ratio, float near_plane, float far_plane) = 0;

    virtual float get_vertical_fov() const = 0;
    virtual float get_aspect_ratio() const = 0;
    virtual float get_near_plane() const = 0;
    virtual float get_far_plane() const = 0;
};