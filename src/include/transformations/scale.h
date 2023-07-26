#ifndef CV_TRANSFORMATIONS_SCALE
#define CV_TRANSFORMATIONS_SCALE

#include "../image.h"

void deimos_apply_up_scaling(Image * img, int factorX, int factorY);
void deimos_apply_down_scaling(Image * img, int factorX, int factorY);

#endif
