#ifndef LAPLACIAN_H
#define LAPLACIAN_H

#include "../image.h"

void cv_apply_laplacian_filter(Image * img, float sigma, int kernSize);

#endif
