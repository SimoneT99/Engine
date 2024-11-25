#include "../headers/pipeline/error.hpp"

void handleOpenGLError(GLenum error, const char* file, int line, bool verbose_handler) {
	/*
		Error handling logic will be here!
	*/
	std::cout << "[OpenGL Error " << error << "]";
	if (verbose_handler) {
		bool verbose_handler;
		std::cout << "found in file : " << file << " and line " << line;
	}
	std::cout << std::endl;
}

void checkOpenGLError(const char* file, int line) {
	int errors = 0;
	while (GLenum error = glGetError()) {
		errors++;
		HANDLE_OPENGL_ERROR(error);
	}
	if (errors != 0) {
		std::cout << errors << " errors found in file: " << file << " and line " << line << std::endl;
		ASSERT(false);
	}
}

void GLClearError(){
	while (glGetError() != GL_NO_ERROR);
}

std::string print_matrix(glm::mat4x4 mat){
    std::ostringstream oss;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            oss << mat[i][j];
            if (j < 3)
                oss << ", "; // Separatore tra gli elementi di una riga
        }
        if (i < 3)
            oss << "\n"; // Vai a capo tra le righe
    }
    return oss.str();
}