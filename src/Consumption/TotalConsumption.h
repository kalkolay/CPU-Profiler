#pragma once

#include "BaseWorker.h"

class TotalConsumption : public BaseWorker
{
public:
    explicit TotalConsumption(const struct Rect&);

    double getCurrentValue() override;

private:
    unsigned long long _previousTotalTicks;
    unsigned long long _previousIdleTicks;

    float calculate(unsigned long long,
                    unsigned long long);
};
