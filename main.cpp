#include <iostream>
#include <string>
#include <memory>
#include <filesystem>

#include "headers/core/object/localObject/OptimizedObject/OptimizedObjectBuilder.hpp"
#include "headers/core/object/localObject/OptimizedObject/OptimizedObject.hpp"
#include "headers/core/object/transform/AbstractTransform.hpp"
#include "headers/core/object/transform/concreteTransform/Transform.hpp"
#include "headers/core/object/AbstractGlobalObject.hpp"
#include "headers/core/object/concreteGlobalObject/GlobalObject.hpp"
#include "headers/core/object/localObject/loader/AbstractLocalObjectLoader.hpp"
#include "headers/core/object/localObject/loader/concreteLoader/ObjLoader.hpp"
#include "headers/core/blackboard/concreteScene/SimpleSceneStub.hpp"
#include "headers/core/blackboard/AbstractScene.hpp"

#include "headers/core/camera/AbstractCamera.hpp"
#include "headers/core/camera/cameraLense/AbstractLense.hpp"
#include "headers/core/camera/cameraObject/AbstractCameraObject.hpp"
#include "headers/core/camera/cameraObject/concreteCameraObject/CameraObject.hpp"
#include "headers/core/camera/cameraLense/concreteLense/Lense.hpp"
#include "headers/core/camera/cameraObject/concreteCameraObject/CameraObject.hpp"
#include "headers/core/camera/AbstractCamera.hpp"
#include "headers/core/camera/AbstractCamera.hpp"
#include "headers/core/camera/concreteCamera/ThreadSafeCamera.hpp"

#include "headers/pipeline/AbstractRenderer.hpp"
#include "headers/pipeline/concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.hpp"
#include "headers/pipeline/concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.hpp"

#include "../include/glm/gtc/quaternion.hpp"
//#include "headers/pipeline/Renderer.hpp"

#define DEBUG true


/**
 * Entry point of the program
 */


int main(int argc, char* argv[]){

    std::string path;

    if (argc > 1) {
        path = argv[1]; // Legge il primo argomento (escludendo il nome del programma)
    } else {
        path = "./assets/cube.obj"; // Percorso di default
    }


    std::unique_ptr<AbstractLocalObjectBuilder> abstractObjectbuilder = std::make_unique<OptimizedObjectBuilder>();
    AbstractLocalObjectLoader* abstractObjectLoader = new ObjLoader(std::move(abstractObjectbuilder), path);
    AbstractLocalObject* abstractObject = abstractObjectLoader->loadObject().release();

    delete(abstractObjectLoader);

    AbstractTransform* transform = new Transform();
    std::shared_ptr<AbstractGlobalObject> globalObject = std::make_shared<GlobalObject>(*abstractObject, *transform);

    delete(transform);

    std::shared_ptr<AbstractLense> lense = std::make_shared<Lense>(
        70.0f,
        1.0f,
        1.0f,
        10.0f
    );

    

    std::shared_ptr<AbstractCameraObject> camera_object = std::make_shared<CameraObject>(
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    #if DEBUG
        std::cout << " fov: " << lense->get_vertical_fov() << 
                     " aspect ratio: " << lense->get_aspect_ratio() << 
                     " near plane: " << lense->get_near_plane() << 
                     " far plane: " << lense->get_far_plane() << std::endl;
    #endif

    #if DEBUG
        std::cout << "position: " << camera_object->get_position().x << " " << camera_object->get_position().y << " " << camera_object->get_position().z  <<
                     " look at: " << camera_object->get_looking_direction().x << " " << camera_object->get_looking_direction().y << " " << camera_object->get_looking_direction().z <<
                     " up: " << camera_object->get_up_vector().x << " " << camera_object->get_position().y << " " << camera_object->get_position().z  << std::endl;
    #endif

    std::shared_ptr<AbstractCamera> camera = std::make_unique<ThreadSafeCamera>(camera_object, lense);

    std::shared_ptr<AbstractScene> abstractScene = std::make_shared<SimpleSceneStub>(camera);

    #if DEBUG
        std::cout << "fov: " << abstractScene->getCamera()->get_lense()->get_vertical_fov() << 
                     " aspect ratio: " << abstractScene->getCamera()->get_lense()->get_aspect_ratio() << 
                     " near plane: " << abstractScene->getCamera()->get_lense()->get_near_plane() << 
                     " far plane: " << abstractScene->getCamera()->get_lense()->get_far_plane() << std::endl;
    #endif

    #if DEBUG
        std::cout << "position: " << abstractScene->getCamera()->get_camera_object()->get_position().x << " " << camera_object->get_position().y << " " << camera_object->get_position().z  <<
                     " look at: " << abstractScene->getCamera()->get_camera_object()->get_looking_direction().x << " " << camera_object->get_looking_direction().y << " " << camera_object->get_looking_direction().z <<
                     " up: " << abstractScene->getCamera()->get_camera_object()->get_up_vector().x << " " << camera_object->get_position().y << " " << camera_object->get_position().z  << std::endl;
    #endif

    #if DEBUG
        std::cout << "View matrix" << std::endl << print_matrix(abstractScene->getCamera()->get_camera_object()->get_view_matrix()) << std::endl; 
        std::cout << "Projection matrix" << std::endl << print_matrix(abstractScene->getCamera()->get_lense()->get_projection_matrix()) << std::endl;
    #endif

    abstractScene->addObject(globalObject);

    std::shared_ptr<AbstractTransform> transform_ptr = globalObject->getTransform();

    /**
     * Since it's a shared pointer these changes should be reflected on the image rendered
     */
    //transform_ptr->scale(0.5,0.5,0.5);
    transform_ptr->rotate(glm::quat( 0.707, 0.0,  0.707, 0.0));
    transform_ptr->translate(0,0,0);

    AbstractRenderer* abstractRenderer = new BaseOpenGLRenderer(
        720,
        720,
        abstractScene
    );

    /**
    transform->translate(1,2,3);
    */

    abstractRenderer->start();

    float temp = 0;
    double tick_rate = 2; //updates in a second
    double delta_time = 1.0/tick_rate;

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;


    while(true){
        
        start = std::chrono::high_resolution_clock::now();
        temp = temp < 2 ? temp + 1 * delta_time : -2;

        abstractScene->getCamera()->get_camera_object()->move_at(glm::vec3(-5.0f, temp, 0.0f));
        abstractScene->getCamera()->get_camera_object()->look_at(glm::vec3(0.0f,0.0f,0.0f));

        end = std::chrono::high_resolution_clock::now();

        elapsed = end - start;

        std::this_thread::sleep_for(
            std::chrono::duration<double>(std::max(0.0, delta_time - elapsed.count()))
        );      
    }

    abstractRenderer->stop();
    delete(abstractRenderer);

    //delete the object

    std::cout << "Done" << std::endl;
    
}