#include <cstdio>
#include <cstdlib>
#include <string.h>

#define ROWS 1080
#define COLS 1920

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define abs(x) ((x)<0 ? -(x) : (x))

bool parse_ppm(const char *filename, const unsigned int width, const unsigned int height, unsigned char *data);
void write_ppm(unsigned *frameData);
void teardown(int exit_status);

