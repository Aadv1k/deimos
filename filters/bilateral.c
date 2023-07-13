#include "./bilateral.h"
#include "./grayscale.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>

 
void compute_spatial_kernel(float *** kernel, float sigma, int size) {
  *kernel = (float**)malloc(sizeof(float**) * size);
  for (int i = 0; i < size; i++) {
    (*kernel)[i] = (float*)malloc(sizeof(float) * size);
    for (int j = 0; j < size; j++) {
      int y = i - size / 2 , x = j - size / 2;
      (*kernel)[i][j] = 1/(sigma * sqrt(2 * M_PI)) * exp(-(x * x + y * y)/ 2 * sigma * sigma);
      printf("%f ", (*kernel)[i][j]);
    }
      printf("\n");
  }
}

void cv_apply_bilateral_filter(Image* img, float sigma) {
  float ** spatialKernel;
  int size = 3;
  compute_spatial_kernel(&spatialKernel, 1.3, size);


  for (int i = 0; i < size; i++) {
    free(spatialKernel[i]);
  }
  free(spatialKernel);

  cv_apply_grayscale(img);
}
