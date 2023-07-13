#ifndef BILATERAL_H
#define BILATERAL_H

#include "../image.h"

void cv_apply_bilateral_filter(Image* img, float sigma, int size);

#endif 
