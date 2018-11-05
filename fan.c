#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "block.h"

typedef struct {
    int level;
    int speed;
} Faninfo;

const char *FILE_FAN = "/proc/acpi/ibm/fan";
const char *REGEX_LEVEL = "^level";
const char *REGEX_SPEED = "^speed";
const int THRESHOLD_YELLOW = 3;
const int THRESHOLD_RED = 5;

void read_stat(char *line, regex_t *regex, int *value)
{
    if (!regexec(regex, line, 0, NULL, 0)) {
        char *token = strtok(line, "\t");
        int i = 0;
        while (token) {
            if (i == 1) {
                int result = (int)strtol(token, NULL, 10);
                if (result > 0)
                    *(value) = result;
            }
            token = strtok(NULL, "\t");
            i++;
        }
    }
}

void read_faninfo(Faninfo *faninfo)
{
    FILE *file = fopen(FILE_FAN, "r");

    if (file != NULL) {
        size_t len;
        ssize_t read;
        char *line = NULL;
        regex_t rlevel;
        regex_t rspeed;
        regcomp(&rlevel, REGEX_LEVEL, 0);
        regcomp(&rspeed, REGEX_SPEED, 0);
        while ((read = getline(&line, &len, file)) != -1) {
            line[strlen(line) - 1] = '\0';
            read_stat(line, &rlevel, &(faninfo->level));
            read_stat(line, &rspeed, &(faninfo->speed));
        }
        free(line);
        fclose(file);
    }
}

void print_faninfo(Faninfo *faninfo)
{
    char color[9];

    set_color(color, faninfo->level, THRESHOLD_RED, THRESHOLD_YELLOW);
    printf("%i %i\n", faninfo->level, faninfo->speed);
    printf("%i %i\n", faninfo->level, faninfo->speed);
    printf("%s\n", color);
}

int main()
{
    Faninfo faninfo;

    faninfo.level = 0;
    faninfo.speed = 0;

    if (access(FILE_FAN, F_OK) != -1)
        read_faninfo(&faninfo);

    print_faninfo(&faninfo);

    return 0;
}
