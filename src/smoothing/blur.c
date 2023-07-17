#include "../include/smoothing/blur.h"

#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


void cv_compute_gaussian_kernel(float *** kernel, int sigma, int size) {
  *kernel = (float**)malloc(sizeof(float*) * size);
  for (int i = 0; i < size; i++) {
    (*kernel)[i] = (float*)malloc(sizeof(float) * size);
    for (int j = 0; j < size; j++) {
        float y =  i - size / 2, x = j - size / 2;
        (*kernel)[i][j] = (1/(2 * M_PI * pow(sigma, 2))) * exp(-(x * x + y * y)/(2*pow(sigma, 2)));
    }
  }
}

void cv_apply_gaussian_blur(Image *image, float sigma, int size) {
  int SIZE = size;
  float **kernel;

  cv_compute_gaussian_kernel(&kernel, sigma, SIZE);

  unsigned char *imageBytes = image->bytes;

  unsigned char *newImageBytes = malloc(image->height * image->width * image->channels * sizeof(unsigned char));

  for (int i = 0; i < image->height; i++) {
    for (int j = 0; j < image->width; j++) {
      for (int c = 0; c < image->channels; c++) {
        float sum = 0.0, sumWeight = 0.0;

        for (int k = 0; k < SIZE; k++) {
          for (int l = 0; l < SIZE; l++) {
            float weight = kernel[k][l];

            int yIndex = i + k - SIZE / 2;
            int xIndex = j + l - SIZE / 2;

            if (yIndex >= 0 && yIndex < image->height && xIndex >= 0 && xIndex < image->width) {
              int pixelIndex = (yIndex * image->width + xIndex) * image->channels + c;
              unsigned char pixelValue = imageBytes[pixelIndex];

              sum += pixelValue * weight;
              sumWeight += weight;
            }
          }
        }

        int pixelIndex = (i * image->width + j) * image->channels + c;
        newImageBytes[pixelIndex] = (unsigned char)(sum / sumWeight);
      }
    }
  }

  memcpy(image->bytes, newImageBytes, image->height * image->width * image->channels * sizeof(unsigned char));

  for (int i = 0; i < SIZE; i++) {
    free(kernel[i]);
  }
  free(kernel);
  free(newImageBytes);
}
