#include "shader.h"

#include "global.h"


void Shader::create_shader()
{
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

void Shader::set_matrices(glm::mat4 transform, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::set_color(Color color)
{
    glUniform4f(glGetUniformLocation(shaderProgram, "newColor"), color.r, color.g, color.b, color.a);
}

void Shader::set_texture(unsigned int texUnit)
{
    glUniform1i(glGetUniformLocation(shaderProgram, "newTexture"), texUnit);
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}
