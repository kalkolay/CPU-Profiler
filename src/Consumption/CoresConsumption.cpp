#include "CoresConsumption.h"

#include <algorithm>

#include <mach/mach.h>

CoresConsumption::CoresConsumption(int n,
                                   const Rect& currentArea)
{
    mach_msg_type_number_t count;
    processor_info_array_t coreInfo;
    host_processor_info(mach_host_self(),
                        PROCESSOR_CPU_LOAD_INFO,
                        &_coreCount,
                        &coreInfo,
                        &count
    );

    _area = currentArea;
    _number = n;
    _cores = (core_info_t*)malloc(sizeof(core_info_t) * _coreCount);

    initializeShaderData();
}

CoresConsumption::~CoresConsumption()
{
    free(_cores);
}

double CoresConsumption::getCurrentValue()
{
    mach_msg_type_number_t count;
    processor_cpu_load_info_t coreInfo;
    natural_t user, system, idle, nice;
    double used, total;

    host_processor_info(mach_host_self(),
                        PROCESSOR_CPU_LOAD_INFO,
                        &_coreCount,
                        (processor_info_array_t*)&coreInfo,
                        &count
    );

#define CORES_CALCULATE_TICKS_DIFF(var, state) \
        var = coreInfo[_number].cpu_ticks[state] - _cores[_number].cpu_ticks[state];

    CORES_CALCULATE_TICKS_DIFF(user,   CPU_STATE_USER)
    CORES_CALCULATE_TICKS_DIFF(system, CPU_STATE_SYSTEM)
    CORES_CALCULATE_TICKS_DIFF(idle,   CPU_STATE_IDLE)
    CORES_CALCULATE_TICKS_DIFF(nice,   CPU_STATE_NICE)

    used = user + system + nice;
    total = system + user + idle + nice;
    _cores[_number].usage = used / total;

#define CORES_ASSIGN_CONSUMPTION_INFO(state) \
        _cores[_number].cpu_ticks[state] = coreInfo[_number].cpu_ticks[state];

    CORES_ASSIGN_CONSUMPTION_INFO(CPU_STATE_USER)
    CORES_ASSIGN_CONSUMPTION_INFO(CPU_STATE_SYSTEM)
    CORES_ASSIGN_CONSUMPTION_INFO(CPU_STATE_IDLE)
    CORES_ASSIGN_CONSUMPTION_INFO(CPU_STATE_NICE)

    return std::min(_cores[_number].usage * 100, 100.);
}
