#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <regex.h>
#include <math.h>

#include "block.h"

typedef enum {
    NONE, CHARGING, DISCHARGING
} Bstate;

typedef struct {
    long   current;
    long   design;
    long   full;
    long   power;
    Bstate state;
} Batteryinfo;

const char *DIR_BATTERY = "/sys/class/power_supply";
const char *FILE_CURRENT = "energy_now";
const char *FILE_DESIGN = "energy_full_design";
const char *FILE_FULL = "energy_full";
const char *FILE_POWER = "power_now";
const char *FILE_STATE = "status";
const char *REGEX_FILE = "^BAT[0-9]";
const char *STATE_CHARGING = "Charging";
const char *STATE_DISCHARGING = "Discharging";
const int THRESHOLD_RED = 75;
const int THRESHOLD_YELLOW = 50;

void read_file(char *path, const char *filename, long *value)
{
    int length = strlen(path) + strlen(filename) + 2;
    char filepath[length];

    snprintf(filepath, length, "%s/%s", path, filename);
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        char *line;
        size_t size;
        getline(&line, &size, file);
        *value = atol(line);
        fclose(file);
    }
}

void read_state(char *path, const char *filename, Bstate *value)
{
    int length = strlen(path) + strlen(filename) + 2;
    char filepath[length];

    snprintf(filepath, length, "%s/%s", path, filename);
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        char *line;
        size_t size;
        getline(&line, &size, file);
        int length = strlen(line);
        line[length - 1] = '\0';
        if (strcmp(line, STATE_CHARGING) == 0)
            *value = CHARGING;
        else if (strcmp(line, STATE_DISCHARGING) == 0)
            *value = DISCHARGING;
        else
            *value = NONE;
        fclose(file);
        free(line);
    }
}

void read_batteryinfo(Batteryinfo *batteryinfo)
{
    DIR *dir = opendir(DIR_BATTERY);

    if (dir != NULL) {
        regex_t regex;
        regcomp(&regex, REGEX_FILE, 0);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_LNK && !regexec(&regex, entry->d_name, 0, NULL, 0)) {
                int length = strlen(DIR_BATTERY) + strlen(entry->d_name) + 2;
                char path[length];

                snprintf(path, length, "%s/%s", DIR_BATTERY, entry->d_name);
                read_file(path, FILE_CURRENT, &batteryinfo->current);
                read_file(path, FILE_DESIGN, &batteryinfo->design);
                read_file(path, FILE_FULL, &batteryinfo->full);
                read_file(path, FILE_POWER, &batteryinfo->power);
                read_state(path, FILE_STATE, &batteryinfo->state);
            }
        }
    }
}

void print_batteryinfo(Batteryinfo *batteryinfo)
{
    double loading = 0.0;
    double life = 0;
    double now = 0;
    char state[2];
    state[1] = '\0';

    if (batteryinfo->full > 0 && batteryinfo->design > 0)
        life = ((double)batteryinfo->full / batteryinfo->design) * 100.0;

    if (batteryinfo->current > 0 && batteryinfo->full > 0)
        now = ((double)batteryinfo->current / batteryinfo->full) * 100.0;

    if (batteryinfo->power > 0 && batteryinfo->current > 0 && batteryinfo->power > 0) {
        if (batteryinfo->state == CHARGING) {
            loading = (double)(batteryinfo->full - batteryinfo->current) / batteryinfo->power;
            strncpy(state, "+", 1);
        } else {
            if (batteryinfo->state == DISCHARGING)
                strncpy(state, "-", 1);
            else
                strncpy(state, " ", 1);
            loading = (double)batteryinfo->current / batteryinfo->power;
        }
    } else {
        loading = 0;
        strncpy(state, " ", 1);
    }

    int hours = loading;
    int minutes = (int)((loading - hours) * 60.0);

    double value = 100 - now;
    char color[COLOR_LENGTH];
    set_color(color, value, THRESHOLD_RED, THRESHOLD_YELLOW);

    printf("%.0f%%%s %02i:%02i %.0f%%\n", now, state, hours, minutes, life);
    printf("%.0f%%%s %02i:%02i %.0f%%\n", now, state, hours, minutes, life);
    printf("%s\n", color);
}

int main()
{
    Batteryinfo batteryinfo;

    batteryinfo.current = 0;
    batteryinfo.design = 0;
    batteryinfo.full = 0;
    batteryinfo.state = NONE;

    read_batteryinfo(&batteryinfo);
    print_batteryinfo(&batteryinfo);

    return 0;
}
