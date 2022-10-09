#include "TotalConsumption.h"

TotalConsumption::TotalConsumption(const struct Rect& currentArea)
    : _previousIdleTicks (0)
    , _previousTotalTicks(0)
{
    _area = currentArea;

    initializeShaderData();
}

float TotalConsumption::calculate(unsigned long long idleTicks,
                                  unsigned long long totalTicks)
{
    auto totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    auto idleTicksSinceLastTime  = idleTicks  - _previousIdleTicks;
    float diff = static_cast<float>(idleTicksSinceLastTime) / totalTicksSinceLastTime;
    float ans = 1.0f;
    if (totalTicksSinceLastTime > 0)
        ans -= diff;
    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ans * 100;
}

double TotalConsumption::getCurrentValue()
{
    // TODO
    return 50.0f;
}
