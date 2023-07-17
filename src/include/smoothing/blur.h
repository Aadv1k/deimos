#ifndef BLUR_H
#define BLUR_H

#include <math.h>
#include <string.h>

#include "../image.h"

void cv_apply_gaussian_blur(Image *image, float sigma, int size);

#endif
