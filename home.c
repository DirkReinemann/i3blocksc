#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>

#include "block.h"

typedef struct {
    long total;
    long available;
    long frsize;
} Homeinfo;

const int THRESHOLD_RED = 75;
const int THRESHOLD_YELLOW = 50;

void readhomeinfo(Homeinfo *homeinfo, char *home)
{
    struct statvfs vfs;

    if (statvfs(home, &vfs) != -1) {
        homeinfo->total = vfs.f_blocks;
        homeinfo->available = vfs.f_bavail;
        homeinfo->frsize = vfs.f_frsize;
    }
}

void printhomeinfo(Homeinfo *homeinfo)
{
    double value = homeinfo->available;
    char unit[3];
    set_unit(unit, &value);
    value *= homeinfo->frsize / 1024;

    char color[9];
    double percent = (double)100.0 - (100.0 * homeinfo->available / homeinfo->total);
    set_color(color, percent, THRESHOLD_RED, THRESHOLD_YELLOW);

    printf("%.2f%s\n", value, unit);
    printf("%.2f%s\n", value, unit);
    printf("%s\n", color);
}


int main()
{
    Homeinfo homeinfo;

    homeinfo.total = 0;
    homeinfo.available = 0;

    char *home = getenv("HOME");
    if (home != NULL)
        readhomeinfo(&homeinfo, home);

    printhomeinfo(&homeinfo);

    return 0;
}
