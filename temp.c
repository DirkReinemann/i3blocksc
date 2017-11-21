#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#include "block.h"

typedef struct {
    int temp;
} Tempinfo;

const char *DIR_THERMAL = "/sys/class/thermal";
const char *FILE_TEMP = "temp";
const char *REGEX_THERMAL = "^thermal_zone";
const int THRESHOLD_RED = 90;
const int THRESHOLD_YELLOW = 70;

void read_tempinfo(Tempinfo *tempinfo)
{
    DIR *dir = opendir(DIR_THERMAL);

    if (dir != NULL) {
        struct dirent *entry;
        regex_t regex;
        regcomp(&regex, REGEX_THERMAL, 0);
        int temp;
        int count;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_LNK && !regexec(&regex, entry->d_name, 0, NULL, 0)) {
                char filepath[BUFSIZ];
                snprintf(filepath, BUFSIZ - 1, "%s/%s/%s", DIR_THERMAL, entry->d_name, FILE_TEMP);
                if (access(filepath, F_OK) != -1) {
                    FILE *file = fopen(filepath, "r");
                    if (file != NULL) {
                        char *line;
                        size_t size;
                        getline(&line, &size, file);
                        temp += atol(line);
                        count++;
                        free(line);
                        fclose(file);
                    }
                }
            }
        }
        closedir(dir);
        tempinfo->temp = temp / count / 1000;
    }
}

void print_tempinfo(Tempinfo *tempinfo)
{
    char color[9];

    set_color(color, tempinfo->temp, THRESHOLD_RED, THRESHOLD_YELLOW);
    printf("%i°C\n", tempinfo->temp);
    printf("%i°C\n", tempinfo->temp);
    printf("%s\n", color);
}

int main()
{
    Tempinfo tempinfo;

    tempinfo.temp = 0;

    read_tempinfo(&tempinfo);
    print_tempinfo(&tempinfo);

    return 0;
}
