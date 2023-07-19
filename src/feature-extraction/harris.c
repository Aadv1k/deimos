#include "../include/feature-extraction/harris.h"
#include "../include/smoothing/grayscale.h"
#include "../include/edge-detection/sobel.h"

#include <assert.h>

void cv_harris_detect_corners(Image * img) {
  cv_apply_grayscale(img);
  cv_apply_sobel_filter(img, 10);

  assert(0 && "Not implemented");
}
