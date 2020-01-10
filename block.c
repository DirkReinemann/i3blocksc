#include <string.h>
#include <stdio.h>

#include "block.h"

const char *COLOR_RED = "#D64937";
const char *COLOR_GREEN = "#4CF054";
const char *COLOR_YELLOW = "#F0A64C";
const char *COLOR_WHITE = "#F9F9F9";
const int COLOR_LENGTH = 8;

void set_color(char *color, double value, double tred, double tyellow)
{
    if (value > tred)
        strncpy(color, COLOR_RED, COLOR_LENGTH);
    else if (value > tyellow)
        strncpy(color, COLOR_YELLOW, COLOR_LENGTH);
    else
        strncpy(color, COLOR_GREEN, COLOR_LENGTH);
    color[COLOR_LENGTH - 1] = '\0';
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
        strncpy(unit, "KB", 3);
        break;
    case 1:
        strncpy(unit, "MB", 3);
        break;
    case 2:
        strncpy(unit, "GB", 3);
        break;
    default:
        unit[0] = '\0';
    }
    unit[2] = '\0';
}
