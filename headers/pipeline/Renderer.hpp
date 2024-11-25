#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../headers/GlobalObject.hpp"
#include "./Camera.hpp"
#include "./error.hpp"


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

        void AddObject(const GlobalObject& object);

        void Render(Camera camera);
};