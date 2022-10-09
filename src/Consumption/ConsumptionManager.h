#pragma once

#include "TotalConsumption.h"
#include "CoresConsumption.h"

#include <thread>

#include <GLFW/glfw3.h>

class ConsumptionManager
{
public:
    ConsumptionManager();

    ~ConsumptionManager();

    void draw();

private:
    TotalConsumption*  graph;
    CoresConsumption** graph2;
    unsigned           numCPU;
    Shader*            shader;
    float              projectionMatrix[16];

    static float* calculateOrtho2dProjection(float*);
};
