#pragma once

#include "BaseWorker.h"

class CoresConsumption : public BaseWorker
{
public:
    CoresConsumption(int,
                     const Rect&);

    ~CoresConsumption();

    double getCurrentValue() override;

private:
    unsigned     _coreCount;
    int          _number;
};
