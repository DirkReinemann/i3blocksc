#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <math.h>

#include "block.h"

typedef struct {
    int  type;
    long total;
    long available;
} Meminfo;

const char *FILE_MEMINFO = "/proc/meminfo";
const char *REGEX_MEM_TOTAL = "^MemTotal";
const char *REGEX_MEM_AVAILABLE = "^MemAvailable";
const char *REGEX_SWAP_TOTAL = "^SwapTotal";
const char *REGEX_SWAP_AVAILABLE = "^SwapFree";
const int THRESHOLD_RED = 75;
const int THRESHOLD_YELLOW = 50;

void read_stat(char *line, const char *sregex, long *value)
{
    regex_t regex;

    regcomp(&regex, sregex, 0);
    if (!regexec(&regex, line, 0, NULL, 0)) {
        char *token = strtok(line, " ");
        int i = 0;
        while (token) {
            if (i == 1) {
                long result = strtol(token, NULL, 10);
                if (result > 0)
                    *(value) = result;
            }
            token = strtok(NULL, " ");
            i++;
        }
    }
}


void read_meminfo(Meminfo *meminfo)
{
    FILE *file = fopen(FILE_MEMINFO, "r");

    if (file != NULL) {
        size_t len;
        ssize_t read;
        char *line = NULL;
        while ((read = getline(&line, &len, file)) != -1) {
            switch (meminfo->type) {
            case 0:
                read_stat(line, REGEX_MEM_TOTAL, &(meminfo->total));
                read_stat(line, REGEX_MEM_AVAILABLE, &(meminfo->available));
                break;

            case 1:
                read_stat(line, REGEX_SWAP_TOTAL, &(meminfo->total));
                read_stat(line, REGEX_SWAP_AVAILABLE, &(meminfo->available));
                break;
            }
        }
        free(line);
        fclose(file);
    }
}


void print_meminfo(Meminfo *meminfo)
{
    char unit[3];
    char color[8];
    double value = meminfo->available;
    double percent = (double)100.0 - (100.0 * meminfo->available / meminfo->total);

    set_unit(unit, &value);
    set_color(color, percent, THRESHOLD_RED, THRESHOLD_YELLOW);

    printf("%.2f%s\n", value, unit);
    printf("%.2f%s\n", value, unit);
    printf("%s\n", color);
}


int main()
{
    Meminfo meminfo;

    meminfo.type = 0;
    meminfo.total = 0;
    meminfo.available = 0;

    char *instance = getenv("BLOCK_INSTANCE");
    if (access(FILE_MEMINFO, F_OK) != -1) {
        if (instance != NULL) {
            if (strlen(instance) > 0)
                if (strcmp(instance, "SWAP") == 0)
                    meminfo.type = 1;
        }
        read_meminfo(&meminfo);
    }

    print_meminfo(&meminfo);

    return 0;
}
