#include <string>
#pragma once

struct StopSign
{
    bool stop = true;
};

struct ProfilingData
{
    std::string module_name;
    uint32_t instance_id;
    uint32_t device_id = 0;
    float process_cost_time = 0.;
    float send_cost_time = 0.;
    uint32_t image_total = -1;
};
