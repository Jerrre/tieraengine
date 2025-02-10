#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "global.h"

void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Render {
    public:
        Render(){};
        Color WHITE = {1.0, 1.0, 1.0, 1.0};
        Color BLACK = {0.0, 0.0, 0.0, 1.0};
        Color RED   = {1.0, 0.0, 0.0, 1.0};
        Color GREEN = {0.0, 1.0, 0.0, 1.0};
        Color BLUE  = {0.0, 0.0, 1.0, 1.0};

        void init_window(int width, int heigth, const char *name);
        int window_should_close();
        void close_window();

        void clear_background(Color color);
        void end_draw();
        Input processInput();
    private:
        GLFWwindow* window;
};