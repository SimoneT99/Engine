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
            float vertical_fov,
            float aspect_ratio,
            float near_plane,
            float far_plane
        ) : vertical_fov(vertical_fov),
        aspect_ratio(aspect_ratio),
        near_plane(near_plane),
        far_plane(far_plane) {}

        glm::mat4x4 get_projection_matrix() const override;

        void set_vertical_fov(float vertical_fov) override;
        void set_aspect_ratio(float aspect_ratio) override;
        void set_near_plane(float near_plane) override;
        void set_far_plane(float far_plane) override;
        void bundled_change(float vertical_fov, float aspect_ratio, float near_plane, float far_plane) override;

        float get_vertical_fov() const override;
        float get_aspect_ratio() const override;
        float get_near_plane() const override;
        float get_far_plane() const override;

};