#pragma once
#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#include "../include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#define VERBOSE_HANDLER false
#define ASSERT(x) if (!(x)){ __debugbreak(); }


void handleOpenGLError(GLenum error, const char* file, int line, bool verbose_handler);
#define HANDLE_OPENGL_ERROR(err) (handleOpenGLError(err, __FILE__, __LINE__, VERBOSE_HANDLER))

void checkOpenGLError(const char *file, int line);
#define CHECK_OPENGL_ERROR() (checkOpenGLError( __FILE__, __LINE__))

/**
* Allow to clear all the errors occoured until now
*/
void GLClearError();
#define CLEAR_OPENGL_ERROR() (GLClearError()) //Just for coherency

/**
* Abstract the call of the opengl funcion!
*/
#define GLCALL(x) CLEAR_OPENGL_ERROR(); x; CHECK_OPENGL_ERROR();

std::string print_matrix(glm::mat4x4 mat);