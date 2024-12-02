#include "../AbstractLense.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"


class Lense : public AbstractLense{

    private:
        float vertical_fov;
        float aspect_ratio;
        float near_plane;
        float far_plane;

    public:

        Lense(
            float fov,
            float aspect_ratio,
            float near_plane,
            float far_plane
        ) : vertical_fov(vertical_fov),
        aspect_ratio(aspect_ratio),
        near_plane(near_plane),
        far_plane(far_plane) {}

        glm::mat4x4 get_projection_matrix() const;

        void set_vertical_fov(float vertical_fov);
        void set_aspect_ratio(float aspect_ratio);
        void set_near_plane(float near_plane);
        void set_far_plane(float far_plane);
        void bundled_change(float vertical_fov, float aspect_ratio, float near_plane, float far_plane);

        float get_vertical_fov() const;
        float set_aspect_ratio() const;
        float set_near_plane() const;
        float set_far_plane() const;

};