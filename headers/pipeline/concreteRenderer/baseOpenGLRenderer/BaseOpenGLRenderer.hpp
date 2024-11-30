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

#define DEBUG_MODE true
#define LOCAL_OBJECT_CHANGES_ENABLED false
#define GLOBAL_OBJECT_CHANGES_ENABLED false
#define PRELOAD_SCENE_BEFORE_START true
#define LOG_ACTIONS true
#define LOG_ACTIONS_VERBOSE false

#if LOG_ACTIONS
    #if LOG_ACTIONS_VERBOSE
        #define LOG(x) {std::cout << x << " at " << __FILE__ << " in line "<< __LINE__ <<  std::endl;}
    #else
        #define LOG(x) {std::cout << x << std::endl;}
    #endif
#else
    #define LOG(x)
#endif

class BaseOpenGLRenderer : public AbstractRenderer{

    private:
        GLFWwindow* window;
        std::unordered_map<unsigned long, OpenGLObjectInformations> object_information_mapper;
    
        /**
         * Shader Management
         */
        std::vector<std::string> parseShader(const std::string& filepath) const;
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShade) const;
        unsigned int compileShader(const std::string& source, unsigned int type) const;
        
        int view_matrix_location = -1;
        int projection_matrix_location = -1;
        unsigned int shader = -1;
        
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