#include "../headers/pipeline/concreteRenderer/baseOpenGLRenderer/BaseOpenGlRenderer.hpp"

std::vector<std::string> BaseOpenGLRenderer::parseShader(const std::string& filepath) const {

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

unsigned int BaseOpenGLRenderer::createShader(const std::string& vertexShader, const std::string& fragmentShader) const{
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

unsigned int BaseOpenGLRenderer::compileShader(const std::string& source, unsigned int type) const{
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

/**
 * Main Stuff
 */

BaseOpenGLRenderer::BaseOpenGLRenderer(
    int width,
    int height,
    std::shared_ptr<AbstractScene> abstractScene
    ) : AbstractRenderer(width, height, abstractScene){

        this->running = false;

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

        glewInit();

        if (glewInit() != GLEW_OK) {
            throw -3;
        }

        GLCALL(glDepthFunc(GL_LEQUAL));
        GLCALL(glEnable(GL_DEPTH_TEST));
    }

void BaseOpenGLRenderer::preprocess(){
    /**
     * BAD: This is bad design since it depends on the shader used...
     */

    std::vector<std::string> shaders = this->parseShader("shaders/SimpleShaders.shader");
    unsigned int shader = this->createShader(shaders.at(0), shaders.at(1));

    GLCALL(glUseProgram(shader));

    GLCALL(this->view_matrix_location = glGetUniformLocation(shader, "viewMatrix"));
    GLCALL(this->projection_matrix_location = glGetUniformLocation(shader, "projectionMatrix"));
    GLCALL(unsigned int blockIndex = glGetUniformBlockIndex(shader, "ModelTransform"));
    GLCALL(glUniformBlockBinding(shader, blockIndex, 0));

    #if PRELOAD_SCENE_BEFORE_START

        this->object_information_mapper.clear();
        for(const std::shared_ptr<AbstractGlobalObject>& object : *this->abstractScene->getAllObjects()){
            this->add_object(object);
        }

    #endif
}

void BaseOpenGLRenderer::start(){
    this->preprocess();
    
    if(this->running){
        std::cout << "Warning: tried to start an already running instance of an openGL renderer";
        return;
    }
    running = true;
    this->render_thread = std::thread(&BaseOpenGLRenderer::render_loop, this);
}

void BaseOpenGLRenderer::stop(){
    
    this->running = false;
    if(this->render_thread.joinable()){
        this->render_thread.join();
    }
}

void BaseOpenGLRenderer::render_loop(){

    /**
     * the render loop is simple for now:
     *  ->we update the global objects in the scene
     *  ->we update the camera
     *  ->we tell OpenGL the VAOs to render
     */

    while(this->running){
        /**
         * Updating stuff
         */
        this->update_objects();
        this->update_camera();

        /**
         * Actual rendering
         */
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
        this->render_VAOs();
        GLCALL(glfwSwapBuffers(this->window));
        GLCALL(glfwPollEvents());
    }
}

/**
 * BAD: This apporach is a pile of dogshit for performance
 */

void BaseOpenGLRenderer::update_objects(){

    #if GLOBAL_OBJECT_CHANGES_ENABLED

    std::shared_ptr<std::vector<std::shared_ptr<AbstractGlobalObject>>> objects_to_update = this->abstractScene->get_changed_objects();

    for(const std::shared_ptr<AbstractGlobalObject>& object : *objects_to_update){
        /**
         * BAD: we need to not update not changed stuff to mantain efficiency...
         */
        bool is_new = false;
        auto map_find_result = this->object_information_mapper.find(object->get_id());

        if(!(map_find_result == this->object_information_mapper.end())){
            
            is_new = true;

            //We need to generate the information object
            unsigned int vao;
            unsigned int vertex_buffer_id;
            unsigned int index_buffer_id;
            unsigned int model_transform_buffer_id;

            GLCALL(glGenVertexArrays(1, &vao));
            GLCALL(glGenBuffers(1, &vertex_buffer_id));
            GLCALL(glGenBuffers(1, &index_buffer_id));
            GLCALL(glGenBuffers(1, &model_transform_buffer_id));

            this->object_information_mapper.insert({object->get_id(), 
                OpenGLObjectInformations(
                    vao,
                    vertex_buffer_id,
                    index_buffer_id,
                    model_transform_buffer_id,
                    0,
                    0
                )
            });
        }
        
        OpenGLObjectInformations openGL_object_informations = is_new ? object_information_mapper.find(object->get_id())->second : map_find_result->second;

        std::vector<glm::vec4> vertexes = object->getObject()->get_vertexes();
        std::vector<glm::uvec3> faces = object->getObject()->get_faces();
        glm::mat4 model_transform = object->getTransform()->get_model_matrix_direct();

        //We work on this vao
        GLCALL(glBindVertexArray(openGL_object_informations.get_vao()));

        #if LOCAL_OBJECT_CHANGES_ENABLED

        //Verticles
        GLCALL(glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec4), object->getObject()->get_vertexes().data(), GL_STATIC_DRAW)); /**BAD: demeter law violated! */

        GLCALL(glEnableVertexAttribArray(0)); /** BAD: we depend on the shader... */
        GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0)); /** BAD: we depend on the vertex informations... */

        //Faces
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, openGL_object_informations.get_index_buffer_id()));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::uvec4), faces.data(), GL_STATIC_DRAW));

        #endif

        //Model Transform
        GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, openGL_object_informations.get_model_transform_buffer()));
        GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW)); //possible error here
        GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, openGL_object_informations.get_model_transform_buffer()));
        GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(model_transform)));

    }

    #endif
}

void BaseOpenGLRenderer::add_object(const std::shared_ptr<AbstractGlobalObject>& object){
    //We need to generate the information object

    unsigned int vao;
    unsigned int vertex_buffer_id;
    unsigned int index_buffer_id;
    unsigned int model_transform_buffer_id;

    std::vector<glm::vec4> vertexes = object->getObject()->get_vertexes();
    std::vector<glm::uvec3> faces = object->getObject()->get_faces();
    glm::mat4 model_transform = object->getTransform()->get_model_matrix_direct();


    //VAO Definition (see below)
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    //Vertex buffer
    GLCALL(glGenBuffers(1, &vertex_buffer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id)); //GL_ARRAY_BUFFER tell OPENGL to use the buffer as vertex attribute data
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec4), vertexes.data(), GL_STATIC_DRAW));

    GLCALL(glEnableVertexAttribArray(0)); //attributo
    GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));

    //Index buffer (faces)
    GLCALL(glGenBuffers(1, &index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::uvec4), faces.data(), GL_STATIC_DRAW));

    //Uniform buffer for model transformation
    GLCALL(glGenBuffers(1, &model_transform_buffer_id));
    GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, model_transform_buffer_id));
    GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW)); //possible error here
    GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, model_transform_buffer_id));


    this->object_information_mapper.insert({object->get_id(), 
        OpenGLObjectInformations(
            vao,
            vertex_buffer_id,
            index_buffer_id,
            model_transform_buffer_id,
            vertexes.size(),
            faces.size()
            )
        });
}

void BaseOpenGLRenderer::update_camera(){
    if(this->abstractScene->hasCameraChanged()){
        /**
         * BAD: violating demeter law!
         */
        glm::mat4x4 view_matrix = this->abstractScene->getCamera()->get_view_matrix();
        glm::mat4x4 projection_matrix = this->abstractScene->getCamera()->get_projection_matrix();
        GLCALL(glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix)));
        GLCALL(glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix)));
    }
}

void BaseOpenGLRenderer::render_VAOs(){
    for(const std::pair<int,OpenGLObjectInformations>& pair : this->object_information_mapper){
        GLCALL(glBindVertexArray(pair.second.get_vao()));
        GLCALL(glDrawElements(GL_TRIANGLES, pair.second.get_number_of_faces(), GL_UNSIGNED_INT, nullptr));
        GLCALL(glBindVertexArray(0)); /** BAD: Still dependent on the shader used... */
    }
}