#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

typedef struct {
    time_t ttstart;
    time_t ttstop;
    int    flag;
} SFile;

typedef struct {
    int minutes;
    int seconds;
} SPrint;

const char *FILENAME = "/tmp/stopwatch";

void difftimes(time_t *ttimea, time_t *ttimeb, SPrint *sprint)
{
    double diff = difftime(*ttimea, *ttimeb);
    int minutes = (int)floor(diff / 60);
    int seconds = (int)diff % 60;

    if (minutes > 60) {
        minutes = 60;
        remove(FILENAME);
    }
    sprint->minutes = minutes;
    sprint->seconds = seconds;
}

int readfile(SFile *sfile)
{
    int result = -1;
    FILE *file = fopen(FILENAME, "rb");

    if (file != NULL) {
        fread(sfile, sizeof(SFile), 1, file);
        fclose(file);
        result = 1;
    }
    return result;
}

int writefile(SFile *sfile)
{
    int result = -1;
    FILE *file = fopen(FILENAME, "wb");

    if (file != NULL) {
        fwrite(sfile, sizeof(SFile), 1, file);
        fclose(file);
        result = 1;
    }
    return result;
}

void handleempty(SPrint *sprint)
{
    if (access(FILENAME, F_OK) != -1) {
        SFile sfile;
        int result = readfile(&sfile);
        if (result != -1) {
            if (sfile.flag == 0) {
                difftimes(&sfile.ttstop, &sfile.ttstart, sprint);
            } else {
                time_t now = time(NULL);
                difftimes(&now, &sfile.ttstart, sprint);
            }
        }
    }
}

void handleleftclick(SPrint *sprint)
{
    if (access(FILENAME, F_OK) != -1) {
        SFile sfile;
        int result = readfile(&sfile);
        if (result != -1) {
            if (sfile.flag == 1) {
                sfile.ttstop = time(NULL);
                sfile.flag = 0;
                writefile(&sfile);
            }
            difftimes(&sfile.ttstop, &sfile.ttstart, sprint);
        }
    } else {
        time_t now = time(NULL);
        SFile sfile;
        sfile.flag = 1;
        sfile.ttstart = now;
        sfile.ttstop = now;
        writefile(&sfile);
    }
}

int main()
{
    SPrint sprint;

    sprint.minutes = 0;
    sprint.seconds = 0;

    char *bbutton = getenv("BLOCK_BUTTON");
    if (bbutton != NULL) {
        if (strlen(bbutton) == 0) {
            handleempty(&sprint);
        } else {
            int button = atoi(bbutton);
            switch (button) {
            case 1:
                handleleftclick(&sprint);
                break;
            case 3:
                remove(FILENAME);
                break;
            }
        }
    }

    printf("%02i:%02i\n%02i:%02i\n\n", sprint.minutes, sprint.seconds, sprint.minutes, sprint.seconds);

    return 0;
}
