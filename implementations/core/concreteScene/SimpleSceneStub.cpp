#include "../headers/core/concreteScene/SimpleSceneStub.hpp"

std::shared_ptr<AbstractCamera> SimpleSceneStub::getCamera() const{
    return this->scene_camera;
}

bool SimpleSceneStub::hasCameraChanged() const{
    return true;
}

void SimpleSceneStub::clearCamera(){
    
};

std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> SimpleSceneStub::getAllObjects() const{
    return this->global_objects;
}

std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> SimpleSceneStub::getChangedObjects() const{
    return this->global_objects;
}

void SimpleSceneStub::clearObjectChanges(){
    
}

void SimpleSceneStub::addObject(std::shared_ptr<AbstractGlobalObject> object){
    
}