#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <stddef.h>

typedef struct
{
    size_t total_allocations;
    size_t total_frees;

    size_t current_memory;
    size_t peak_memory;

} MemoryTracker;

void memory_tracker_init(MemoryTracker *tracker);

void* tracked_malloc(
    MemoryTracker *tracker,
    size_t size
);

void tracked_free(
    MemoryTracker *tracker,
    void *ptr,
    size_t size
);

void memory_tracker_report(
    const MemoryTracker *tracker
);

#endif