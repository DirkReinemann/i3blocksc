#ifndef BLOCK_H_
#define BLOCK_H_

extern const char *COLOR_RED;
extern const char *COLOR_GREEN;
extern const char *COLOR_YELLOW;
extern const char *COLOR_WHITE;
extern const int COLOR_LENGTH;

void set_color(char *color, double value, double tred, double tyellow);
void set_unit(char *unit, double *value);

#endif
