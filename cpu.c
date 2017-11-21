#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "block.h"

typedef struct {
    long total;
    long idle;
} Cpuinfo;

const char *FILE_STAT = "/proc/stat";
const char *REGEX_CPU = "^cpu[0-9]";
const int THRESHOLD_YELLOW = 50;
const int THRESHOLD_RED = 75;

void read_cpuinfo(Cpuinfo *cpuinfo)
{
    FILE *file = fopen(FILE_STAT, "r");

    if (file != NULL) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        long total = 0;
        long idle = 0;
        regex_t regex;
        regcomp(&regex, REGEX_CPU, 0);
        while ((read = getline(&line, &len, file)) != -1) {
            if (!regexec(&regex, line, 0, NULL, 0)) {
                int column = 0;
                char *token = strtok(line, " ");

                while (token) {
                    long value = strtol(token, NULL, 10);
                    if (column == 4)
                        idle += value;
                    total += value;
                    token = strtok(NULL, " ");
                    column++;
                }
            }
        }
        cpuinfo->total = total;
        cpuinfo->idle = idle;
        free(line);
        fclose(file);
    }
}

void print_cpuinfo(Cpuinfo *cpuinfoone, Cpuinfo *cpuinfotwo)
{
    char color[8];
    long idle = cpuinfotwo->idle - cpuinfoone->idle;
    long total = cpuinfotwo->total - cpuinfoone->total;
    double percent = (double)(1000.0 * (total - idle) / total + 5.0) / 10.0;

    set_color(color, percent, THRESHOLD_RED, THRESHOLD_YELLOW);
    printf("%.2f%%\n", percent);
    printf("%.2f%%\n", percent);
    printf("%s\n", color);
}


int main()
{
    Cpuinfo cpuinfoone;
    Cpuinfo cpuinfotwo;

    cpuinfoone.total = 0;
    cpuinfoone.idle = 0;
    cpuinfotwo.total = 0;
    cpuinfotwo.idle = 0;

    if (access(FILE_STAT, F_OK) != -1) {
        read_cpuinfo(&cpuinfoone);
        sleep(1);
        read_cpuinfo(&cpuinfotwo);
    }

    print_cpuinfo(&cpuinfoone, &cpuinfotwo);

    return 0;
}
