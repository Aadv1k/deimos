#include "./bilateral.h"
#include "./grayscale.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include <string.h>

#include <stdio.h>
 
void compute_spatial_kernel(float *** kernel, float sigma, int size) {
  *kernel = (float**)malloc(sizeof(float**) * size);
  for (int i = 0; i < size; i++) {
    (*kernel)[i] = (float*)malloc(sizeof(float) * size);
    for (int j = 0; j < size; j++) {
      int y = i - size / 2 , x = j - size / 2;
      (*kernel)[i][j] = 1/(sigma * sqrt(2 * M_PI)) * exp(-(x * x + y * y)/ 2 * sigma * sigma);
    }
  }
}


unsigned char compute_bilateral_filter_for_channel(Image* img, float sigma, int kernSize, int x, int y, int c) {
    int width = img->width;
    int height = img->height;
    int ch = img->channels;

    int centerIndex = (y * width + x) * ch + c;
    int centerValue = img->bytes[centerIndex];
    float sumWeights = 0.0;
    float weightedSum = 0.0;

    for (int i = 0; i < kernSize; i++) {
        for (int j = 0; j < kernSize; j++) {
            if (y + i >= height || x + j >= width)
                continue;

            int curIndex = ((y + i) * width + x + j) * ch + c;
            int curValue = img->bytes[curIndex];
            int diff = centerValue - curValue;

            float rangeWeight = exp(-(diff * diff) / (2 * sigma * sigma));

            weightedSum += rangeWeight * curValue;
            sumWeights += rangeWeight;
        }
    }

    return (unsigned char)(weightedSum / sumWeights);
}

void cv_apply_bilateral_filter(Image* img, float sigma, int kernSize) {
  float **spatialKernel;
  compute_spatial_kernel(&spatialKernel, sigma, kernSize);

  int width = img->width;
  int height = img->height;
  int ch = img->channels;

  unsigned char* tempBytes = (unsigned char*)malloc(width * height * ch * sizeof(unsigned char));

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char R = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 0);
      unsigned char G = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 1);
      unsigned char B = compute_bilateral_filter_for_channel(img, sigma, kernSize, j, i, 2);

      tempBytes[(i * width + j) * ch + 0] = R;
      tempBytes[(i * width + j) * ch + 1] = G;
      tempBytes[(i * width + j) * ch + 2] = B;
    }
  }

  memcpy(img->bytes, tempBytes, width * height * ch * sizeof(unsigned char));

  free(tempBytes);

  puts("Bilateral filter applied successfully!");

  for (int i = 0; i < kernSize; i++) {
    free(spatialKernel[i]);
  }
  free(spatialKernel);
}
