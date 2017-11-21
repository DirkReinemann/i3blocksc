#include <string.h>

#include "block.h"

const char *COLOR_RED = "#FF0000";
const char *COLOR_GREEN = "#00FF00";
const char *COLOR_YELLOW = "#FFFF00";
const int COLOR_LENGTH = 8;

void set_color(char *color, double value, double tred, double tyellow)
{
    if (value > tred)
        strncpy(color, COLOR_RED, COLOR_LENGTH);
    else if (value > tyellow)
        strncpy(color, COLOR_YELLOW, COLOR_LENGTH);
    else
        strncpy(color, COLOR_GREEN, COLOR_LENGTH);
}

void set_unit(char *unit, double *value)
{
    int iteration = 0;
    double next = *value / 1024;

    while (next > 1) {
        *value = next;
        next = *value / 1024;
        iteration++;
    }

    switch (iteration) {
    case 0:
        strncpy(unit, "KB", 2);
        break;
    case 1:
        strncpy(unit, "MB", 2);
        break;
    case 2:
        strncpy(unit, "GB", 2);
        break;
    }
}
