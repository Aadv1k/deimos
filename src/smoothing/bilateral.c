#include "../include/smoothing/bilateral.h"

#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
 
void compute_spatial_kernel(float *** kernel, float sigma, int size) {
  *kernel = (float**)malloc(sizeof(float**) * size);

  const int sigSq = 2 * sigma * sigma;
  const int inverseSigmaRoot = 1/(sigma * sqrt(2 * M_PI));

  for (int i = 0; i < size; i++) {
    (*kernel)[i] = (float*)malloc(sizeof(float) * size);
    for (int j = 0; j < size; j++) {
      int y = i - size / 2 , x = j - size / 2;
      (*kernel)[i][j] = inverseSigmaRoot * exp(-(x * x + y * y)/sigSq);
    }
  }
}

unsigned char compute_bilateral_filter_for_channel(Image* img, float sigma, int kernSize, int x, int y, int c) {
    int width = img->width;
    int height = img->height;
    int ch = img->channels;

    int centerIndex = (y * width + x) * ch + c;
    int centerValue = img->bytes[centerIndex];
    float totalSum = 0.0;
    float totalWeightedSum = 0.0;

    for (int i = 0; i < kernSize; i++) {
        for (int j = 0; j < kernSize; j++) {
            if (y + i >= height || x + j >= width)
                continue;

            int curIndex = ((y + i) * width + x + j) * ch + c;
            int curValue = img->bytes[curIndex];
            int diff = centerValue - curValue;

            float rangeWeight = exp(-(diff * diff) / (2 * sigma * sigma));

            totalWeightedSum += rangeWeight * curValue;
            totalSum += rangeWeight;
        }
    }

    return (unsigned char)(totalWeightedSum / totalSum);
}

void cv_apply_bilateral_filter(Image* img, float sigma, int kernSize) {
  int width = img->width;
  int height = img->height;
  int ch = img->channels;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char R = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 0);
      unsigned char G = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 1);
      unsigned char B = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 2);

      img->bytes[(i * width + j) * ch + 0] = R;
      img->bytes[(i * width + j) * ch + 1] = G;
      img->bytes[(i * width + j) * ch + 2] = B;
    }
  }
}
