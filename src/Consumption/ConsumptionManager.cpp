#include "ConsumptionManager.h"

#include "../Utilities/Constants.h"

ConsumptionManager::ConsumptionManager()
    : numCPU( std::thread::hardware_concurrency() )
    , shader( new Shader(projectionMatrix) )
{
    // Dimensions and location of the coord system for total CPU consumption (in the form of rectangle)
    const BaseWorker::Rect totalConsumptionGraphSize = { 100, 100, 10, 10 };
    graph = new TotalConsumption(totalConsumptionGraphSize);

    if (!numCPU)
        numCPU = 1;

    graph2 = new CoresConsumption*[numCPU];

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);

    calculateOrtho2dProjection(projectionMatrix);

    graph->start();

    for (int i = 0; i < numCPU; ++i)
    {
        // Dimensions and location of the coord system for CPU consumption per core (in the form of rectangle)
        const BaseWorker::Rect coresConsumptionGraphSize = {50, 50, (double)(120 + i % 2 * 60),
                                                            (double)(i / 2 * 70 + 10)};
        graph2[i] = new CoresConsumption(i, coresConsumptionGraphSize);
        graph2[i]->start();
    }
}

ConsumptionManager::~ConsumptionManager()
{
    delete shader;
    delete[] graph;
    for (int i = 0; i < numCPU; ++i)
        delete[] graph2[i];
    delete[] graph2;
    numCPU = 0;
}

float* ConsumptionManager::calculateOrtho2dProjection(float* projectionMatrix)
{
    // this is basically from
    const float zNear = -1.0f;
    const float zFar = 1.0f;
    const float inv_z = 1.0f / (zFar - zNear);
    const float inv_y = -1.0f / HEIGHT;
    const float inv_x = 1.0f / WIDTH;

    //first column
    *projectionMatrix++ = 2.0f * inv_x;
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = 0.0f;

    //second
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = 2.0f * inv_y;
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = 0.0f;

    //third
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = 0.0f;
    *projectionMatrix++ = -2.0f * inv_z;
    *projectionMatrix++ = 0.0f;

    //fourth
    *projectionMatrix++ = -WIDTH * inv_x;
    *projectionMatrix++ = -HEIGHT * inv_y;
    *projectionMatrix++ = -(zFar + zNear) * inv_z;
    *projectionMatrix = 1.0f;

    return projectionMatrix;
}

void ConsumptionManager::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3.0);

    graph->drawCurve(shader);

    for (size_t i = 0; i < numCPU; ++i)
        graph2[i]->drawCurve(shader);

    glFlush();
}
