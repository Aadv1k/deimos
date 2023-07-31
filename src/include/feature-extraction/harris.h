#include "../image.h" 

#define SOBEL_K_SIZE 3
#define HARRIS_K_CONST 0.4

void cv_harris_detect_corners(Image * img, float threshold);
