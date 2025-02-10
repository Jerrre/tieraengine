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