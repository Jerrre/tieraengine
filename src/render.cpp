#include "render.h"

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Render::init_window(int width, int heigth, const char *name){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    } 

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, heigth, name, NULL, NULL);
    if(!window){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }  

    glfwSetKeyCallback(window, key_callback);

    create_default_shader_program();
    glEnable(GL_DEPTH_TEST);

}
int Render::window_should_close(){
    return glfwWindowShouldClose(window);
}
void Render::close_window(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Render::clear_background(Color color){
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Render::end_draw(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Render::create_default_shader_program(){
    const char *vertexShaderSrc  = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "uniform mat4 transform;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main(){\n"
        "gl_Position = projection * view * model *vec4(aPos, 1.0);\n"
        "TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
        "}\0";
    const char *fragmentShaderSrc = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D newTexture;\n"
        "uniform vec4 newColor;\n"
        "void main(){\n"
        "FragColor = texture(newTexture, TexCoord)*newColor;}\0";

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int complileSuccess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &complileSuccess);
    if (!complileSuccess){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR compiling vertex shader" << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &complileSuccess);
    if (!complileSuccess){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR compiling fragment shader" << std::endl;
    }
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &complileSuccess);
    if (!complileSuccess){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR compiling shader program" << std::endl;
    }    

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Render::set_default_shader_color(Color color)
{
    glUniform4f(glGetUniformLocation(shaderProgram, "newColor"), color.r, color.g, color.b, color.a);
}

void Render::set_default_shader_texture(unsigned int texUnit)
{
    glUniform1i(glGetUniformLocation(shaderProgram, "newTexture"), texUnit);
}

void Render::set_default_shader_matrices(glm::mat4 transform, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}
