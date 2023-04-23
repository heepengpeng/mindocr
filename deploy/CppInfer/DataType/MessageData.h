#ifndef MESSAGE_DATA_H
#define MESSAGE_DATA_H
#include <string>


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
#endif