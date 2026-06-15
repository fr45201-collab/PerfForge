#include "../include/profiler.h"
#include "../include/json_exporter.h"

void slow_function()
{
    volatile int sum = 0;

    for(int i = 0; i < 10000000; i++)
    {
        sum += i;
    }
}

int main()
{
    ProfileRecord profiler = {0};

    profiler_start(
        &profiler,
        "slow_function"
    );

    slow_function();

    profiler_stop(&profiler);

    profiler_print(&profiler);

    export_profile_json(
        &profiler,
        "report.json"
    );

    return 0;
}