#include "../include/profiler.h"

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
    ProfileRecord record = {0};

    profiler_start(
        &record,
        "slow_function"
    );

    slow_function();

    profiler_stop(&record);

    profiler_print(&record);

    return 0;
}