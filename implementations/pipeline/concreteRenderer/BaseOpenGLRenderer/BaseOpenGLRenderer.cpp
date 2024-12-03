#include "../headers/pipeline/concreteRenderer/baseOpenGLRenderer/BaseOpenGLRenderer.hpp"

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
        this->object_information_mapper = std::unordered_map<unsigned long, OpenGLObjectInformations>();

        if (!glfwInit()){
            throw -1;
        }

        glfwSetErrorCallback(GlfwErrorCallback);

        LOG("Window preprocessing...")

        /* We can specify the version of OPENGL and the mode */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //this will make required the explicit definition of the VAO
        glfwWindowHint(GLFW_DEPTH_BITS, 24);

        LOG("Creating window...")
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);
        if (!window)
        {
            LOG("Error in window generation...")
            glfwTerminate();
            throw -2;
        }

        LOG("Setting context...")

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glewInit();

        if (glewInit() != GLEW_OK) {
            throw -3;
        }

        LOG("Depth test setup...")
        GLCALL(glDepthFunc(GL_LEQUAL));
        GLCALL(glEnable(GL_DEPTH_TEST));

        LOG("Initial setup done...")
    }

void BaseOpenGLRenderer::preprocess(){
    /**
     * BAD: This is bad design since it depends on the shader used...
     */
    LOG("Preprocessing step...")
    LOG("Preparing shaders...")
    std::vector<std::string> shaders = this->parseShader("./shaders/SimpleShaders.shader");
    this->shader = this->createShader(shaders.at(0), shaders.at(1));

    GLCALL(glUseProgram(shader));

    #if DEBUG_MODE
        int currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        std::cout << "Current shader " << currentProgram << std::endl;
    #endif

    GLCALL(this->view_matrix_location = glGetUniformLocation(shader, "viewMatrix"));
    GLCALL(this->projection_matrix_location = glGetUniformLocation(shader, "projectionMatrix"));

    GLCALL(unsigned int blockIndex = glGetUniformBlockIndex(shader, "ModelTransform"));
    GLCALL(glUniformBlockBinding(shader, blockIndex, 0));

    
    #if PRELOAD_SCENE_BEFORE_START
        LOG("Preloading scene...")
        this->object_information_mapper.clear();
        LOG("Mapper cleared...")
        for(const std::shared_ptr<AbstractGlobalObject>& object : *this->abstractScene->getAllObjects()){
            this->add_object(object);
        }
    #endif
}

void BaseOpenGLRenderer::start(){
    LOG("Starting scene called...")
    this->preprocess();
    if(this->running){
        LOG("Warning: tried to start an already running instance of an openGL renderer")
        return;
    }  
    running = true;
    LOG("Releasing the context in main thread...")
    glfwMakeContextCurrent(nullptr);

    LOG("Starting scene thread...")
    this->render_thread = std::thread(&BaseOpenGLRenderer::render_loop, this);
}

void BaseOpenGLRenderer::stop(){
    LOG("Stopping scene called...")
    this->running = false;
    if(this->render_thread.joinable()){
        this->render_thread.join();
        glfwMakeContextCurrent(this->window);
    }
}

void BaseOpenGLRenderer::render_loop(){

    //We have to take the context in this thread
    LOG("Taking the context control...")
    glfwMakeContextCurrent(this->window);

    /**
     * the render loop is simple for now:
     *  ->we update the global objects in the scene
     *  ->we update the camera
     *  ->we tell OpenGL the VAOs to render
     */

    glfwSwapInterval(0); //half refreshrate

    LOG("Entering render loop...")
    while(this->running){
        
        /**
         * Updating stuff
         */
        LOG("Updating Objects...")
        this->update_objects();
        LOG("Updating Camera...")
        this->update_camera();

        /**
         * Actual rendering
         */
        LOG("Clearing buffers...")
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
        LOG("Sending VAOs...")
        this->render_VAOs();
        LOG("Ending this frame render...")
        GLCALL(glfwSwapBuffers(this->window));
        GLCALL(glfwPollEvents());
        LOG("Cicle done...")
    }

    LOG("Releasing the context in child thread...")
    glfwMakeContextCurrent(nullptr);
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

    LOG("Adding object...")

    unsigned int vao;
    unsigned int vertex_buffer_id;
    unsigned int index_buffer_id;
    unsigned int model_transform_buffer_id;

    std::vector<glm::vec4> vertexes = object->getObject()->get_vertexes();
    std::vector<glm::uvec3> faces = object->getObject()->get_faces();
    glm::mat4 model_transform = object->getTransform()->get_model_matrix_direct();


    //VAO Definition (see below)
    LOG("VAO definition...")
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    //Vertex buffer
    LOG("Vertex buffer definition...")
    GLCALL(glGenBuffers(1, &vertex_buffer_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id)); //GL_ARRAY_BUFFER tell OPENGL to use the buffer as vertex attribute data
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(glm::vec4), vertexes.data(), GL_STATIC_DRAW));

    GLCALL(glEnableVertexAttribArray(0)); //attributo
    GLCALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));

    //Index buffer (faces)
    LOG("Index buffer definition...")
    GLCALL(glGenBuffers(1, &index_buffer_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::uvec3), faces.data(), GL_STATIC_DRAW));

    //Uniform buffer for model transformation
    LOG("Model transform buffer definition...")
    GLCALL(glGenBuffers(1, &model_transform_buffer_id));
    GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, model_transform_buffer_id));
    GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW)); //possible error here
    GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, model_transform_buffer_id));

    GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4x4), glm::value_ptr(model_transform)));   

    LOG("Pushing into mapper...")
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
    LOG("Done...")
}

void BaseOpenGLRenderer::update_camera(){
    if(this->abstractScene->hasCameraChanged()){
        /**
         * BAD: violating demeter law!
         */
        LOG("Getting camera data...")
        
        #if DEBUG_MODE
            int currentProgram = 0;
            glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
            std::cout << "Current shader " << currentProgram << std::endl;
        #endif

        glm::mat4x4 view_matrix = this->abstractScene->getCamera()->get_camera_object()->get_view_matrix();
        LOG(print_matrix(view_matrix))
        glm::mat4x4 projection_matrix = this->abstractScene->getCamera()->get_lense()->get_projection_matrix();
        LOG(print_matrix(projection_matrix))

        LOG("Pushing view matrix data...")
        #if DEBUG_MODE
            if (glm::value_ptr(view_matrix) == nullptr) {
                std::cerr << "Errore: Puntatore alla matrice view_matrix non valido" << std::endl;
            }
        #endif
        GLCALL(glUniformMatrix4fv(this->view_matrix_location, 1, GL_FALSE, glm::value_ptr(view_matrix)));
        LOG("Pushing projection matrix data...")
        #if DEBUG_MODE
            if (glm::value_ptr(projection_matrix) == nullptr) {
                std::cerr << "Errore: Puntatore alla matrice projection_matrix non valido" << std::endl;
            }
        #endif
        GLCALL(glUniformMatrix4fv(this->projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix)));
        LOG("Done updating camera...")
    }
}

void BaseOpenGLRenderer::render_VAOs(){
    for(const std::pair<int,OpenGLObjectInformations>& pair : this->object_information_mapper){
        GLCALL(glBindVertexArray(pair.second.get_vao()));
        GLCALL(glDrawElements(GL_TRIANGLES, pair.second.get_number_of_faces() * 3, GL_UNSIGNED_INT, nullptr));
    }
    GLCALL(glBindVertexArray(0));
}