#include "../headers/pipeline/AbstractRenderer.hpp"
#include "../headers/pipeline/concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.hpp"
#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/gtc/type_ptr.hpp"
#include "./OpenGLObjectInformations.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <atomic>

#pragma once

/**
 * Toy renderer Using OpenGL
 */

#define DEBUG_MODE True
#define LOCAL_OBJECT_CHANGES_ENABLED False
#define GLOBAL_OBJECT_CHANGES_ENABLED False
#define PRELOAD_SCENE_BEFORE_START True

class BaseOpenGLRenderer : public AbstractRenderer{

    private:
        GLFWwindow* window;
        std::unordered_map<int, OpenGLObjectInformations> object_information_mapper;
    
        /**
         * Shader Management
         */
        std::vector<std::string> parseShader(const std::string& filepath) const;
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShade) const;
        unsigned int compileShader(const std::string& source, unsigned int type) const;
        
        int view_matrix_location = -1;
        int projection_matrix_location = -1;

        
        /**
         * Render loop
         */
        void preprocess();
        void render_loop();
        void update_objects();
        void update_camera();
        void render_VAOs();

        /**
         * Helper functions
         */

        void add_object(const std::shared_ptr<AbstractGlobalObject>& object);


        /**
         * Multithreading
         */

        std::thread render_thread;
        std::atomic<bool> running;

    public:
        BaseOpenGLRenderer(
            int width,
            int height,
            std::shared_ptr<AbstractScene> abstractScene
        );

        void start();
        void stop();    

};