#pragma once

#include "BaseWorker.h"

#include <mach/mach.h>

class CoresConsumption : public BaseWorker
{
    typedef struct _core_info_t
    {
        natural_t cpu_ticks[CPU_STATE_MAX];
        double usage;
    } core_info_t;

public:
    CoresConsumption(int,
                     const Rect&);

    ~CoresConsumption();

    double getCurrentValue() override;

private:
    unsigned     _coreCount;
    core_info_t* _cores;
    int          _number;
};
