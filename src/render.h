#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct Color{
    float r;
    float g;
    float b;
    float a;
};

/*--------------------*/
/* CALLBACK FUNCTIONS */
/*--------------------*/
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Render {
    public:
        Render(){
        };

        const Color WHITE = {1.0, 1.0, 1.0, 1.0};
        const Color BLACK = {0.0, 0.0, 0.0, 1.0};
        const Color RED   = {1.0, 0.0, 0.0, 1.0};
        const Color GREEN = {0.0, 1.0, 0.0, 1.0};
        const Color BLUE  = {0.0, 0.0, 1.0, 1.0};

        /*-----------------*/
        /* WINDOW HANDLING */
        /*-----------------*/
        void init_window(int width, int heigth, const char *name);
        int window_should_close();
        void close_window();


        void clear_background(Color color);
        void end_draw();
        void set_default_shader_matrices(glm::mat4 transform, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
        unsigned int shaderProgram;
    private:
        GLFWwindow* window;
        
        void create_default_shader_program();
        void set_default_shader_color(Color color);
        void set_default_shader_texture(unsigned int textureID);

};