#include "AbstractCameraObject.hpp"
#include "AbstractLense.hpp"

#include <memory>

/**
 * Abstract definition of a camera to put in the scene.
 */

class AbstractCamera{

    public:
        virtual std::shared_ptr<AbstractCameraObject> get_camera_object() const = 0;
        virtual std::shared_ptr<AbstractLense> get_lense() const = 0;

};