#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../headers/core/object/AbstractGlobalObject.hpp"
#include "../headers/core/concreteCamera/Camera.hpp"
#include "../headers/pipeline/concreteRenderer/baseOpenGLRenderer/OpenGLErrorHandling.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



/**
 * FAT CLASS just to explore openGL
 */
class Renderer{

    private:
        GLFWwindow* window;
        unsigned int object_vao;
        unsigned int number_of_faces;
    
        /**
         * Support methods
         */
        std::vector<std::string> parseShader(const std::string& filepath) const;
        unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShade) const;
        unsigned int compileShader(const std::string& source, unsigned int type) const;

    public:
        Renderer(int width, int height);

        void AddObject(const AbstractGlobalObject& object);

        void Render(Camera camera);
};