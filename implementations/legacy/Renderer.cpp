#include "../headers/pipeline/Renderer.hpp" 

Renderer::Renderer(int width, int height){
    /* Initialize the library */
    if (!glfwInit()){
        throw -1;
    }

    /* We can specify the version of OPENGL and the mode */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //this will make required the explicit definition of the VAO
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        throw -2;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* We can limit the frame rate of the window */
    glfwSwapInterval(2);

    glewInit();

    if (glewInit() != GLEW_OK) {
        throw -3;
    }
}

void Renderer::AddObject(const AbstractGlobalObject& object){

    std::shared_ptr<AbstractLocalObject> local_object = object.getObject();
    std::shared_ptr<AbstractTransform> transform = object.getTransform();

    std::vector<glm::vec4> vertices = local_object->get_vertexes();
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> faces = local_object->get_faces();

    unsigned int number_of_verticles = vertices.size();
    unsigned int number_of_faces = faces.size();
    this->number_of_faces = number_of_faces;

    glm::mat4x4 model_transform_matrix = object.getTransform()->get_model_matrix_direct();

    std::vector<unsigned int> indices;
    for (const auto& face : faces) {
        indices.push_back(std::get<0>(face));
        indices.push_back(std::get<1>(face));
        indices.push_back(std::get<2>(face));
    }

    //VAO Definition (see below)
    unsigned int vao;
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));


    //Vertex buffer
    unsigned int vertex_buffer_id;
    GLCALL(glGenBuffers(1, &vertex_buffer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id)); //GL_ARRAY_BUFFER tell OPENGL to use the buffer as vertex attribute data
    GLCALL(glBufferData(GL_ARRAY_BUFFER, number_of_verticles * sizeof(glm::vec4), vertices.data(), GL_STATIC_DRAW));

    GLCALL(glEnableVertexAttribArray(0)); //attributo
    GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));

    //Index buffer (faces)
    unsigned int index_buffer_id;
    GLCALL(glGenBuffers(1, &index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));

    //Uniform buffer for model transformation
    unsigned int model_transform_buffer;
    GLCALL(glGenBuffers(1, &model_transform_buffer));
    GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, model_transform_buffer));
    GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW)); //possible error here
    GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, model_transform_buffer));

    GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(model_transform_matrix)));   

    this->object_vao = vao;
}

std::vector<std::string> Renderer::parseShader(const std::string& filepath) const {

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    ShaderType currentType = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                currentType = ShaderType::VERTEX;
            }
            if (line.find("fragment") != std::string::npos) {
                currentType = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)currentType] << line << "\n";
        }
    }

    //PROBLEM: how we return multiple variables??
    // -> solution: a struct

    return std::vector<std::string>{ ss[0].str(), ss[1].str() };
}

unsigned int Renderer::createShader(const std::string& vertexShader, const std::string& fragmentShader) const{
    unsigned int program = glCreateProgram();
    unsigned int vs = this->compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = this->compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    //the idea is to link the shaders to the openGL program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //the shader are linked, we don't need the sources anymore (like the intermediates when the cpp program is compiled)
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Renderer::compileShader(const std::string& source, unsigned int type) const{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); //since we need a c string
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
 
    /*
    * The result of the compilation is stored in the state of the opengl program...
    *  ...we can retrive it to check if something went wrong
    * Is not different from when we ran the cuda program on the device and then we had to manually
    *   check for errors...
    */
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char)); //Evil hack to alloc in the stack the string
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Compilation failed: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

void Renderer::Render(Camera camera){

    std::vector<std::string> shaders = this->parseShader("shaders/SimpleShaders.shader");

    unsigned int shader = this->createShader(shaders.at(0), shaders.at(1));

    GLCALL(glUseProgram(shader));

    GLCALL(int view_matrix_location = glGetUniformLocation(shader, "viewMatrix"));
    GLCALL(int projection_matrix_location = glGetUniformLocation(shader, "projectionMatrix"));
    GLCALL(unsigned int blockIndex = glGetUniformBlockIndex(shader, "ModelTransform"));
    GLCALL(glUniformBlockBinding(shader, blockIndex, 0));

    glm::mat4x4 view_matrix = camera.get_view_matrix();
    glm::mat4x4 projection_matrix = camera.get_projection_matrix();

    std::cout << "View matrix \n" << print_matrix(view_matrix) << std::endl;
    std::cout << "Projection matrix \n" << print_matrix(projection_matrix) << std::endl;

    GLCALL(glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix)));
    GLCALL(glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix)));
    GLCALL(glDepthFunc(GL_LEQUAL));
    
    /**
     * Now we run the render
     */

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(this->window)){
         /* Render here */
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
        GLCALL(glUseProgram(shader));
        GLCALL(glBindVertexArray(this->object_vao));
        GLCALL(glDrawElements(GL_TRIANGLES, this->number_of_faces*3, GL_UNSIGNED_INT, nullptr));
        GLCALL(glBindVertexArray(0));
        GLCALL(glfwSwapBuffers(window));
        /* Poll for and process events */
        GLCALL(glfwPollEvents());
    }

    glDeleteProgram(shader);

    glfwTerminate();
}