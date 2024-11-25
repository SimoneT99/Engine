#include <iostream>
#include <string>
#include <memory>
#include <filesystem>

#include "headers/object/OptimizedObject/OptimizedObjectBuilder.hpp"
#include "headers/object/loader/concreteLoaders/ObjLoader.hpp"
#include "headers/transform/AbstractTransform.hpp"
#include "headers/transform/concreteTransforms/Transform.hpp"
#include "headers/GlobalObject.hpp"
#include "../include/glm/gtc/quaternion.hpp"
#include "headers/pipeline/Camera.hpp"
#include "headers/pipeline/Renderer.hpp"
#include "headers/pipeline/error.hpp"

#define DEBUG true


/**
 * Entry point of the program
 */


int main(int argc, char* argv[]){    

    #if DEBUG
    std::cout << "Starting..." << std::endl;
    #endif

    std::unique_ptr<AbstractObjectBuilder> abstractObjectbuilder = std::make_unique<OptimizedObjectBuilder>();

    #if DEBUG
    std::cout << "abstractObjectBuilder done..." << std::endl;
    #endif

    AbstractLoader* abstractObjectLoader = new ObjLoader(std::move(abstractObjectbuilder), "./teapot.obj");

    #if DEBUG
    std::cout << "abstractObjectLoader done..." << std::endl;
    #endif

    AbstractObject* abstractObject = abstractObjectLoader->loadObject().release();

    #if DEBUG
    std::cout << "abstractObject done..." << std::endl;
    #endif

    #if DEBUG
    std::cout << "abstractObjectbuilder deleted..." << std::endl;
    #endif

    delete(abstractObjectLoader);

    #if DEBUG
    std::cout << "deleting stuff done..." << std::endl;
    #endif
    //use the object

    //std::cout << static_cast<std::string>(*abstractObject) << std::endl;

    AbstractTransform* transform = new Transform();
    GlobalObject* globalObject = new GlobalObject(*abstractObject, *transform);
    delete(transform);

    std::cout << static_cast<std::string>(*globalObject) << std::endl;

    #if DEBUG
    std::cout << "appling modifications to the object tranform" << std::endl;
    #endif

    transform = globalObject->getTransform();

    transform->scale(0.5,0.5,0.5);
    transform->rotate(glm::quat( 0.707, 0.0,  0.707, 0.0));
    transform->translate(0,0,0);
    
    /**
    transform->translate(1,2,3);
    
    

    */

    std::cout << static_cast<std::string>(*globalObject) << std::endl;

    Camera camera = Camera(
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        70.0f,
        1.0f,
        1.0f,
        10.0f
    );

    Renderer renderer = Renderer(720, 720);

    renderer.AddObject(*globalObject);

    renderer.Render(camera);

    //delete the object

    std::cout << "Done" << std::endl;

    delete(abstractObject);
    delete(globalObject);
}