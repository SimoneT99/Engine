#include "../AbstractLenseProxy.hpp"
#include <mutex>

/**
 * NOTE: This is developed only to fuction with a writing thread and a reading thread,
 *  If you use more then one the behaviour is undefined
 */

class LenseThreadSafetyProxy : public AbstractLenseProxy{

    private:
        glm::mat4x4 projection_matrix_backup;
        std::mutex lense_write_mutex;
        
        mutable std::mutex proxy_modify_mutex; //evil...

        float vertical_fov_backup;
        float aspect_ratio_backup;
        float near_plane_backup;
        float far_plane_backup;

        inline void update_projection_matrix();

    public:
        glm::mat4x4 get_projection_matrix() const;

        void set_vertical_fov(float fov) override;
        void set_aspect_ratio(float aspect_ratio) override;
        void set_near_plane(float near_plane) override;
        void set_far_plane(float far_plane) override;
        void bundled_change(float fov, float aspect_ratio, float near_plane, float far_plane)  override;

        float get_vertical_fov() const override;
        float get_aspect_ratio() const override;
        float get_near_plane() const override;
        float get_far_plane() const override;
};