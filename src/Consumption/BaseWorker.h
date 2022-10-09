#pragma once

#include "../Utilities/Constants.h"
#include "../Shader/Shader.h"

#include <array>

class BaseWorker
{
public:
    struct Rect
    {
        double width, height, left, top;
    };

    BaseWorker();

    void drawCurve(Shader *shader);

    void start();

    virtual double getCurrentValue() = 0;

private:
    int  _countGridPoints;
    int  _currentInterval;
    bool _stopPush;        // Indicates when we have to stop incrementing _currentInterval

    const int _coordOnPoint = 5;   // Coefficient for displaying points
    const int _steps        = 10;  // Number of cells on both horizontal and vertical sides of the graph

    GLuint VBO;
    GLuint VAO;

    std::array<double, STEPS_INTERVAL> _points;

    inline void fillVertices(GLfloat*, int);

    void update();

    static void* threadStartStatic(void*);
    [[noreturn]] void threadStart();

protected:
    Rect _area;

    void initializeShaderData();
};
