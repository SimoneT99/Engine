#include "../headers/core/camera/concreteProxy/CameraThreadSafetyProxy.hpp"

#define WRAP_CAMERA_LOCK(x){std::unique_lock<std::mutex> camera_lock(this->camera_mutex); x; camera_lock.unlock();}
#define WRAP_BACKUP_LOCK(x){std::unique_lock<std::mutex> backup_lock(this->backup_mutex); x; backup_lock.unlock();}
#define WRAP_BACKUP_AND_UPDATE_MATRIX(x) {WRAP_BACKUP_LOCK(x; this->update_view_matrix())}

void CameraObjectThreadSafetyProxy::look_at(glm::vec3 point){
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->abstractCamera->look_at(point))
}

void CameraObjectThreadSafetyProxy::move_at(glm::vec3 location){
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->abstractCamera->move_at(location))
}

void CameraObjectThreadSafetyProxy::set_up_vector(glm::vec3 up){
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->abstractCamera->set_up_vector(up))
}

void CameraObjectThreadSafetyProxy::set_camera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up){
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->abstractCamera->set_camera(position, look_at, up))
}

inline void CameraObjectThreadSafetyProxy::update_view_matrix(){
    this->view_matrix_backup = this->abstractCamera->get_view_matrix();
}

glm::mat4x4 CameraObjectThreadSafetyProxy::get_view_matrix() const{
    if(this->backup_mutex.try_lock()){
        this->backup_mutex.unlock();
        return this->view_matrix_backup;
    }else{
        return this->abstractCamera->get_view_matrix();
    }
}

glm::vec3 CameraObjectThreadSafetyProxy::get_position() const{
    if(this->backup_mutex.try_lock()){
        this->backup_mutex.unlock();
        return this->position_backup;
    }else{
        return this->abstractCamera->get_position();
    }
}

glm::vec3 CameraObjectThreadSafetyProxy::get_looking_direction() const{
    if(this->backup_mutex.try_lock()){
        this->backup_mutex.unlock();
        return this->looking_direction_backup;
    }else{
        return this->abstractCamera->get_looking_direction();
    }
}

glm::vec3 CameraObjectThreadSafetyProxy::get_up_vector() const {
    if(this->backup_mutex.try_lock()){
        this->backup_mutex.unlock();
        return this->up_vector_backup;
    }else{
        return this->abstractCamera->get_up_vector();
    }
}