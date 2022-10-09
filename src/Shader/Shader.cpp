#include "Shader.h"

#include <iostream>

Shader::Shader(GLfloat* projectionMatrix)
    : _projectionMatrix(projectionMatrix)
{
    const GLchar* vShaderCode = "#version 330 core\n"
                                "layout (location = 0) in vec2 position;\n"
                                "layout (location = 1) in vec3 color;\n"
                                "uniform mat4 uProjectionMatrix;\n"
                                "out vec3 ourColor;\n"
                                "void main()\n"
                                "{\n"
                                "   ourColor = color;\n"
                                "   gl_Position = uProjectionMatrix*(vec4(position, 0, 1.0));\n"
                                "}\0";

    const GLchar* fShaderCode = "#version 330 core\n"
                                "in vec3 ourColor;\n"
                                "out vec4 color;\n"
                                "void main()\n"
                                "{\n"
                                "   color = vec4(ourColor, 1.0f);\n"
                                "}\0";

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[MAX_BUFFER_LENGTH];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, MAX_BUFFER_LENGTH, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, MAX_BUFFER_LENGTH, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    _program = glCreateProgram();
    glAttachShader(_program, vertex);
    glAttachShader(_program, fragment);
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_program, MAX_BUFFER_LENGTH, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(_program);

    GLuint projectionMatrixRef = glGetUniformLocation(_program, "uProjectionMatrix");

    glUniformMatrix4fv(projectionMatrixRef, 1, GL_FALSE, _projectionMatrix);
}
