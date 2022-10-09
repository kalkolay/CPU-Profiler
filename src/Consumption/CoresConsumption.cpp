#include "CoresConsumption.h"

CoresConsumption::CoresConsumption(int n,
                                   const Rect& currentArea)
{
    _area = currentArea;
    _number = n;

    initializeShaderData();
}

CoresConsumption::~CoresConsumption()
{

}

double CoresConsumption::getCurrentValue()
{
    // TODO
    return 0.0f;
}
