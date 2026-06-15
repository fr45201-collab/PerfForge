#ifndef JSON_EXPORTER_H
#define JSON_EXPORTER_H

#include "profiler.h"

int export_profile_json(
    const ProfileRecord *record,
    const char *filename
);

#endif