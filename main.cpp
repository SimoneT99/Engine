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
#include "headers/core/concreteScene/SimpleSceneStub.hpp"
#include "headers/core/AbstractScene.hpp"
#include "headers/core/AbstractCamera.hpp"
#include "headers/core/concreteCamera/Camera.hpp"
#include "headers/pipeline/AbstractRenderer.hpp"
#include "headers/pipeline/concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.hpp"



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

    std::shared_ptr<AbstractCamera> camera = std::make_shared<Camera>(
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        70.0f,
        1.0f,
        1.0f,
        10.0f
    );

    std::shared_ptr<AbstractScene> abstractScene = std::make_shared<SimpleSceneStub>(camera);
    abstractScene->addObject(globalObject);

    std::shared_ptr<AbstractTransform> transform_ptr = globalObject->getTransform();

    /**
     * Since it's a shared pointer these changes should be reflected on the image rendered
     */
    transform_ptr->scale(0.5,0.5,0.5);
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

    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    abstractRenderer->stop();
    delete(abstractRenderer);

    //delete the object

    std::cout << "Done" << std::endl;
    
}