#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwTerminate();
    return 0;
}