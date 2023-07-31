#ifndef CV_TRANSFORMATIONS_ROTATE
#define CV_TRANSFORMATIONS_ROTATE

#include "../image.h"


void rotationSwap(unsigned char* x, unsigned char* y);

typedef enum {
  DEG_90 = 90,
  MINUS_DEG_90 = -90,
  DEG_180 = 180
} RotationDegree;

void deimos_apply_rotation(Image * img, RotationDegree deg);

#endif
