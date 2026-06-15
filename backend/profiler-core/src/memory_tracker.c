#include "../include/memory_tracker.h"

#include <stdio.h>
#include <stdlib.h>

void memory_tracker_init(
    MemoryTracker *tracker
)
{
    tracker->total_allocations = 0;
    tracker->total_frees = 0;

    tracker->current_memory = 0;
    tracker->peak_memory = 0;
}

void* tracked_malloc(
    MemoryTracker *tracker,
    size_t size
)
{
    void *ptr = malloc(size);

    if(ptr)
    {
        tracker->total_allocations++;

        tracker->current_memory += size;

        if(tracker->current_memory >
           tracker->peak_memory)
        {
            tracker->peak_memory =
                tracker->current_memory;
        }
    }

    return ptr;
}

void tracked_free(
    MemoryTracker *tracker,
    void *ptr,
    size_t size
)
{
    if(ptr)
    {
        free(ptr);

        tracker->total_frees++;

        tracker->current_memory -= size;
    }
}

void memory_tracker_report(
    const MemoryTracker *tracker
)
{
    printf("\n");
    printf("========== MEMORY REPORT ==========\n");

    printf("Allocations : %zu\n",
           tracker->total_allocations);

    printf("Frees       : %zu\n",
           tracker->total_frees);

    printf("Current     : %zu bytes\n",
           tracker->current_memory);

    printf("Peak        : %zu bytes\n",
           tracker->peak_memory);

    printf("Leaks       : %zu bytes\n",
           tracker->current_memory);

    printf("===================================\n");
}