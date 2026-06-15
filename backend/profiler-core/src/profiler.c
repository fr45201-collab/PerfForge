#include "../include/profiler.h"

#include <stdio.h>
#include <string.h>

static long long current_time_ns()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ((long long)ts.tv_sec * 1000000000LL)
           + ts.tv_nsec;
}

void profiler_start(ProfileRecord *record,
                    const char *function_name)
{
    strncpy(record->function_name,
            function_name,
            sizeof(record->function_name) - 1);

    record->start_ns = current_time_ns();
}

void profiler_stop(ProfileRecord *record)
{
    record->end_ns = current_time_ns();

    long long diff =
        record->end_ns - record->start_ns;

    record->elapsed_ms =
        diff / 1000000.0;

    record->call_count++;
}

void profiler_print(const ProfileRecord *record)
{
    printf("\n========== PERFFORGE ==========\n");

    printf("Function : %s\n",
           record->function_name);

    printf("Calls    : %d\n",
           record->call_count);

    printf("Runtime  : %.3f ms\n",
           record->elapsed_ms);

    printf("===============================\n");
}