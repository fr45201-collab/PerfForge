#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <stddef.h>

#define MAX_ALLOCATIONS 1024

typedef struct
{
    void *ptr;
    size_t size;
    int active;

} AllocationRecord;

typedef struct
{
    size_t total_allocations;
    size_t total_frees;

    size_t current_memory;
    size_t peak_memory;

    AllocationRecord allocations[MAX_ALLOCATIONS];

} MemoryTracker;

/* Initialization */

void memory_tracker_init(
    MemoryTracker *tracker
);

/* Allocation API */

void* tracked_malloc(
    MemoryTracker *tracker,
    size_t size
);

void tracked_free(
    MemoryTracker *tracker,
    void *ptr
);

/* Allocation Registry */

int find_allocation(
    MemoryTracker *tracker,
    void *ptr
);

/* Reports */

void memory_tracker_report(
    const MemoryTracker *tracker
);

void memory_tracker_leaks(
    const MemoryTracker *tracker
);

#endif