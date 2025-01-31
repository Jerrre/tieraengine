#include <iostream>

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

}
int Render::window_should_close(){
    return glfwWindowShouldClose(window);
}
void Render::close_window(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Render::create_mesh(float vertices[], int vertexCount, unsigned int indices[], int indexCount){
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
void Render::clear_background(Color color){
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Render::draw(Color color){
    int vertexColorLoc = glGetUniformLocation(shaderProgram, "newColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLoc, color.r, color.g, color.b, color.a);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Render::create_default_shader_program(){
    const char *vertexShaderSrc  = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\0";
    const char *fragmentShaderSrc = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 newColor;\n"
        "void main(){\n"
        "FragColor = newColor;}\0";

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
        std::cout << "ERROR compiling default vertex shader" << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &complileSuccess);
    if (!complileSuccess){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR compiling default fragment shader" << std::endl;
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
