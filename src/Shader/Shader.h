#pragma once

#include <GL/glew.h>

#include "../Utilities/Constants.h"

class Shader
{
public:
    explicit Shader(GLfloat*);

    void use() const;

private:
    GLuint   _program;
    GLfloat* _projectionMatrix;
};
