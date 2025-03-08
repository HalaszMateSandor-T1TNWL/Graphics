#include "Color/color.h"

#ifndef LINE_H_
#define LINE_H_

typedef struct Line {

  float bpoint[2];
  float epoint[2];
  Color color;
  
} Line;

#define MAX_LINE_COUNT 100

#endif