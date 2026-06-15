#include "../include/json_exporter.h"

#include <stdio.h>

int export_profile_json(
    const ProfileRecord *record,
    const char *filename
)
{
    FILE *file = fopen(filename, "w");

    if (!file)
    {
        return -1;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"function_name\": \"%s\",\n", record->function_name);
    fprintf(file, "  \"call_count\": %d,\n", record->call_count);
    fprintf(file, "  \"elapsed_ms\": %.3f\n", record->elapsed_ms);
    fprintf(file, "}\n");

    fclose(file);

    return 0;
}