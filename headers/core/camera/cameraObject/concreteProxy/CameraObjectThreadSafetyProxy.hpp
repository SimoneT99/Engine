#include "../AbstractCameraObjectProxy.hpp"
#include <mutex>

/**
 * Thread safety proxy to allow the camera to be changed and used in parallel
 *  by different threads without fear of race conditions.
 * The proxy is indipendent on the concrete implementation of the camera
 * ISSUE: We bind the update of the camera to the calculation of the matrixes, could be problematic
 *  performance wise since if the game update is set to be faster than the refresh rate we do more calculation
 *  than actually needed... 
 * ISSUE: What if we want thread safety also on other part of the camera, like fov, far plane, etc...
 */

class CameraObjectThreadSafetyProxy : public AbstractCameraObjectProxy{

    private:
        glm::mat4x4 view_matrix_backup;

        glm::vec3 position_backup;
        glm::vec3 looking_direction_backup;
        glm::vec3 up_vector_backup;

        std::mutex camera_mutex;
        mutable std::mutex backup_mutex; //evil

        inline void update_view_matrix();

    public:
        
        CameraObjectThreadSafetyProxy(std::shared_ptr<AbstractCameraObject> camera_object) 
        : AbstractCameraObjectProxy(camera_object),
          position_backup(camera_object->get_position()),
          looking_direction_backup(camera_object->get_looking_direction()),
          up_vector_backup(camera_object->get_up_vector()),
          view_matrix_backup(camera_object->get_view_matrix())
        {}

        void move_at(glm::vec3 location) override;
        void look_at(glm::vec3 point) override;
        void set_up_vector(glm::vec3 up) override;

        void set_camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up) override;

        glm::mat4x4 get_view_matrix() const override;

        glm::vec3 get_position() const override;
        glm::vec3 get_looking_direction() const override;
        glm::vec3 get_up_vector() const override;
           
};