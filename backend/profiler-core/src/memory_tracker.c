#include "../include/memory_tracker.h"

#include <stdio.h>
#include <stdlib.h>

/* ==========================================
   Internal Helpers
   ========================================== */

int find_allocation(
    MemoryTracker *tracker,
    void *ptr
)
{
    for(int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        if(tracker->allocations[i].active &&
           tracker->allocations[i].ptr == ptr)
        {
            return i;
        }
    }

    return -1;
}

/* ==========================================
   Initialization
   ========================================== */

void memory_tracker_init(
    MemoryTracker *tracker
)
{
    tracker->total_allocations = 0;
    tracker->total_frees = 0;

    tracker->current_memory = 0;
    tracker->peak_memory = 0;

    for(int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        tracker->allocations[i].ptr = NULL;
        tracker->allocations[i].size = 0;
        tracker->allocations[i].active = 0;
    }
}

/* ==========================================
   Allocation
   ========================================== */

void* tracked_malloc(
    MemoryTracker *tracker,
    size_t size
)
{
    void *ptr = malloc(size);

    if(ptr == NULL)
    {
        return NULL;
    }

    tracker->total_allocations++;

    tracker->current_memory += size;

    if(tracker->current_memory >
       tracker->peak_memory)
    {
        tracker->peak_memory =
            tracker->current_memory;
    }

    for(int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        if(!tracker->allocations[i].active)
        {
            tracker->allocations[i].ptr = ptr;
            tracker->allocations[i].size = size;
            tracker->allocations[i].active = 1;
            break;
        }
    }

    return ptr;
}

/* ==========================================
   Free
   ========================================== */

void tracked_free(
    MemoryTracker *tracker,
    void *ptr
)
{
    if(ptr == NULL)
    {
        return;
    }

    int index = find_allocation(
        tracker,
        ptr
    );

    if(index == -1)
    {
        printf(
            "[WARNING] Unknown pointer free detected\n"
        );
        return;
    }

    tracker->current_memory -=
        tracker->allocations[index].size;

    tracker->total_frees++;

    tracker->allocations[index].active = 0;

    free(ptr);
}

/* ==========================================
   Leak Report
   ========================================== */

void memory_tracker_leaks(
    const MemoryTracker *tracker
)
{
    printf("\n");
    printf("======= ACTIVE ALLOCATIONS =======\n");

    int leaks_found = 0;

    for(int i = 0; i < MAX_ALLOCATIONS; i++)
    {
        if(tracker->allocations[i].active)
        {
            leaks_found = 1;

            printf(
                "Leak: %zu bytes at %p\n",
                tracker->allocations[i].size,
                tracker->allocations[i].ptr
            );
        }
    }

    if(!leaks_found)
    {
        printf("No memory leaks detected.\n");
    }

    printf("==================================\n");
}

/* ==========================================
   Summary Report
   ========================================== */

void memory_tracker_report(
    const MemoryTracker *tracker
)
{
    printf("\n");

    printf(
        "========== MEMORY REPORT ==========\n"
    );

    printf(
        "Allocations : %zu\n",
        tracker->total_allocations
    );

    printf(
        "Frees       : %zu\n",
        tracker->total_frees
    );

    printf(
        "Current     : %zu bytes\n",
        tracker->current_memory
    );

    printf(
        "Peak        : %zu bytes\n",
        tracker->peak_memory
    );

    printf(
        "Leaks       : %zu bytes\n",
        tracker->current_memory
    );

    printf(
        "===================================\n"
    );
}