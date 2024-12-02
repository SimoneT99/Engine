#include "./AbstractCameraObject.hpp"
#include <memory>

class AbstractCameraObjectProxy : public AbstractCameraObject {

    protected:
        std::shared_ptr<AbstractCameraObject> abstractCamera;

    public:
        AbstractCameraObjectProxy(std::shared_ptr<AbstractCameraObject> abstractCamera) :
        abstractCamera(std::move(abstractCamera)){}
};