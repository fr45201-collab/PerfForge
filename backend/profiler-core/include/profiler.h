#ifndef PROFILER_H
#define PROFILER_H

#include <time.h>

typedef struct
{
    char function_name[128];

    long long start_ns;
    long long end_ns;

    double elapsed_ms;

    int call_count;

} ProfileRecord;

void profiler_start(ProfileRecord *record,
                    const char *function_name);

void profiler_stop(ProfileRecord *record);

void profiler_print(const ProfileRecord *record);

#endif