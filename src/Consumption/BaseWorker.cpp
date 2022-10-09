#include "BaseWorker.h"

#include <unistd.h>
#include <pthread.h>

BaseWorker::BaseWorker()
    : _currentInterval( 0 )
    , _stopPush       ( false )
    , _points         ( std::array<double, STEPS_INTERVAL>() )
{
    for (size_t i = 0; i < STEPS_INTERVAL; ++i)
        _points[i] = 0;
}

inline void BaseWorker::fillVertices(GLfloat* vertices, int i)
{
    // Grid color in RGB
    const GLfloat gridColor[3] = { 217.0 / 0xff, 234.0 / 0xff, 244.0 / 0xff };

    for (auto j = 0; j < 3; ++j)
        vertices[i * _coordOnPoint + 2 + j] = gridColor[j];
    for (auto j = 0; j < 3; ++j)
        vertices[(i + 1) * _coordOnPoint + 2 + j] = gridColor[j];
}

void BaseWorker::initializeShaderData()
{
    _countGridPoints = (_steps + 1) * 4;
    GLsizeiptr size = (_countGridPoints + STEPS_INTERVAL) * _coordOnPoint * sizeof(GLfloat);
    auto* vertices = new GLfloat[(_countGridPoints + STEPS_INTERVAL) * _coordOnPoint]();

    bool direction = false;

    for (int i = 0, k = 0; i < _countGridPoints; i += 2, k += 2)
    {
        if (k % ((_steps + 1) * 2) == 0)
            k = 0;

        if (i / ((_steps + 1) * 2) == 0)
        {
            vertices[i * _coordOnPoint] = _area.left + (_area.width / _steps) * (int)(i / 2);
            vertices[(i + (int)direction) * _coordOnPoint + 1] = _area.top + _area.height;

            vertices[(i + 1) * _coordOnPoint] = _area.left + (_area.width / _steps) * (int)((i + 1) / 2);
            vertices[(i + (int)(!direction)) * _coordOnPoint + 1] = _area.top;
        }
        else
        {
            vertices[(i + (int)(direction)) * _coordOnPoint] = _area.left;
            vertices[i * _coordOnPoint + 1] = _area.top + (_area.height / _steps) * (int)(k / 2);

            vertices[(i + (int)(!direction)) * _coordOnPoint] = _area.left + _area.width;
            vertices[(i + 1) * _coordOnPoint + 1] = _area.top + (_area.height / _steps) * (int)((k + 1) / 2);
        }

        fillVertices(vertices, i);

        direction = !direction;
    }

    for (size_t i = 0; i < STEPS_INTERVAL; ++i)
    {
        vertices[(_countGridPoints + i) * _coordOnPoint] = _area.left + (_area.width / (STEPS_INTERVAL - 1)) * i;
        vertices[(_countGridPoints + i) * _coordOnPoint + 4] = 0.0f;
    }

    /// Initialize and activate VAO & VBO using OpenGL API
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _coordOnPoint * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, _coordOnPoint * sizeof(GLfloat),
                          (GLvoid*)(2 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void BaseWorker::drawCurve(Shader* shader)
{
    update();

    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, _countGridPoints);
    glDrawArrays(GL_LINE_STRIP, _countGridPoints, _currentInterval);
    glBindVertexArray(0);
    glUseProgram(0);
}

void BaseWorker::update()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    auto* mapBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (size_t i = 0; i < _currentInterval; ++i)
    {
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 1] = _area.top
                + (1.0f - (_points[i]) / 100.0f) * _area.height;
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 2] = _points[i] / 100.0f;
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 3] = 1.0f - _points[i] / 100.0f;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void* BaseWorker::threadStartStatic(void* Param)
{
    auto* This = (BaseWorker*)Param;
    This->threadStart();
}

[[noreturn]] void BaseWorker::threadStart()
{
    while (true)
    {
        if (!_stopPush)
            _currentInterval++;

        if (_currentInterval > STEPS_INTERVAL - 1)
        {
            for (size_t i = 1; i < STEPS_INTERVAL; ++i)
                _points[i - 1] = _points[i];

            _stopPush = true;
        }

        _points[_currentInterval - 1] = getCurrentValue();

        usleep(UPDATE_TIME);
    }
}

void BaseWorker::start()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, threadStartStatic, (void*)this);
}
