#include "..\headers\core\camera\cameraLense\concreteProxy\LenseThreadSafetyProxy.hpp"

#define WRAP_LENSE_LOCK(x){std::unique_lock<std::mutex> lense_lock(this->lense_write_mutex); x; lense_lock.unlock();}
#define WRAP_BACKUP_LOCK(x){std::unique_lock<std::mutex> backup_lock(this->proxy_modify_mutex); x; backup_lock.unlock();}
#define WRAP_BACKUP_AND_UPDATE_MATRIX(x) {WRAP_BACKUP_LOCK(x; this->update_projection_matrix())}

/**
 * Modifiers
 */

void LenseThreadSafetyProxy::set_vertical_fov(float vertical_fov){
    WRAP_LENSE_LOCK(this->abstract_lense->set_vertical_fov(vertical_fov))
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->vertical_fov_backup = vertical_fov)
}

void LenseThreadSafetyProxy::set_aspect_ratio(float aspect_ratio){

    WRAP_LENSE_LOCK(this->abstract_lense->set_aspect_ratio(aspect_ratio))
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->aspect_ratio_backup = aspect_ratio);
    
}

void LenseThreadSafetyProxy::set_near_plane(float near_plane){

    WRAP_LENSE_LOCK(this->abstract_lense->set_near_plane(near_plane))
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->near_plane_backup = near_plane);
    
}

void LenseThreadSafetyProxy::set_far_plane(float far_plane){

    WRAP_LENSE_LOCK(this->abstract_lense->set_far_plane(far_plane))
    WRAP_BACKUP_AND_UPDATE_MATRIX(this->far_plane_backup = far_plane)

}

void LenseThreadSafetyProxy::bundled_change(float vertical_fov, float aspect_ratio, float near_plane, float far_plane){
    WRAP_LENSE_LOCK(this->abstract_lense->bundled_change(vertical_fov, aspect_ratio, near_plane, far_plane))
    WRAP_BACKUP_AND_UPDATE_MATRIX(
        this->vertical_fov_backup = this->abstract_lense->get_vertical_fov();
        this->aspect_ratio_backup = this->abstract_lense->get_aspect_ratio();
        this->near_plane_backup = this->abstract_lense->get_near_plane();
        this->far_plane_backup = this->abstract_lense->get_far_plane();
        )
}


/**
 * NOTE: what happens if the data passed is invalid? who has to check?
 */

inline void LenseThreadSafetyProxy::update_projection_matrix(){
    this->projection_matrix_backup = this->abstract_lense->get_projection_matrix();
}

glm::mat4x4 LenseThreadSafetyProxy::get_projection_matrix() const{
    if(this->proxy_modify_mutex.try_lock()){
        this->proxy_modify_mutex.unlock();
        return this->projection_matrix_backup;
    }else{
        return this->abstract_lense->get_projection_matrix();
    }
}


float LenseThreadSafetyProxy::get_vertical_fov() const{
    if(this->proxy_modify_mutex.try_lock()){
        this->proxy_modify_mutex.unlock();
        return this->vertical_fov_backup;
    }else{
        return this->abstract_lense->get_vertical_fov();
    }
}

float LenseThreadSafetyProxy::get_aspect_ratio() const{
    if(this->proxy_modify_mutex.try_lock()){
        this->proxy_modify_mutex.unlock();
        return this->aspect_ratio_backup;
    }else{
        return this->abstract_lense->get_aspect_ratio();
    }
}

float LenseThreadSafetyProxy::get_near_plane() const{
    if(this->proxy_modify_mutex.try_lock()){
        this->proxy_modify_mutex.unlock();
        return this->near_plane_backup;
    }else{
        return this->abstract_lense->get_near_plane();
    }
}

float LenseThreadSafetyProxy::get_far_plane() const{
    if(this->proxy_modify_mutex.try_lock()){
        this->proxy_modify_mutex.unlock();
        return this->far_plane_backup;
    }else{
        return this->abstract_lense->get_far_plane();
    }
}