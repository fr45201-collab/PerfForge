#include "../include/memory_tracker.h"

int main()
{
    MemoryTracker tracker;

    memory_tracker_init(
        &tracker
    );

    int *arr =
        tracked_malloc(
            &tracker,
            100 * sizeof(int)
        );

    tracked_free(
        &tracker,
        arr
    );

    memory_tracker_report(
        &tracker
    );

    memory_tracker_leaks(
        &tracker
    );

    return 0;
}