#include "render.h"

void Render::error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}
void Render::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void Render::framebuffer_size_callback(GLFWwindow* window, int width, int height)
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}
int Render::window_should_close(){
    return glfwWindowShouldClose(window);
}
void Render::close_window(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Render::startDraw()
{
    float currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void Render::clear_background(Color color){
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Render::end_draw(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

Input Render::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        return UP;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        return DOWN;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        return LEFT;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        return RIGHT;

    return NO_INPUT;
        
}

glm::vec2 Render::getMouseOffset()
{
    double xPos, yPos;
    glm::vec2 mouseOffset;
    glfwGetCursorPos(window, &xPos, &yPos);
    float lastX = SCREEN_WIDTH / 2;
    float lastY = SCREEN_HEIGHT / 2;

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    mouseOffset = {xOffset, yOffset};

    return mouseOffset;
}
