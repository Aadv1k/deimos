#include "../include/smoothing/blur.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void cv_compute_gaussian_kernel(float kernel[SIZE][SIZE], int sigma, int size) {
  float sigmaSquared = pow(sigma, 2);
  float twoSigmaSquared = 2 * sigmaSquared;
  float weightSum = 0.0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      float y = i - size / 2;
      float x = j - size / 2;
      float weight = exp(-(x * x + y * y) / twoSigmaSquared) / (M_PI * twoSigmaSquared);
      kernel[i][j] = weight;
      weightSum += weight;
    }
  }

  /*
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      kernel[i][j] /= weightSum;
    }
  }
  */
}

void cv_apply_gaussian_blur(Image *image, float sigma, int size) {
  float kernel[SIZE][SIZE];
  cv_compute_gaussian_kernel(kernel, sigma, size);

  unsigned char *imageBytes = image->bytes;
  unsigned char *newImageBytes = malloc(image->height * image->width * image->channels * sizeof(unsigned char));

  for (int i = 0; i < image->height; i++) {
    for (int j = 0; j < image->width; j++) {
      for (int c = 0; c < image->channels; c++) {
        float sum = 0.0;

        for (int k = 0; k < size; k++) {
          for (int l = 0; l < size; l++) {
            float weight = kernel[k][l];

            int yIndex = i + k - size / 2;
            int xIndex = j + l - size / 2;

            if (yIndex >= 0 && yIndex < image->height && xIndex >= 0 && xIndex < image->width) {
              int pixelIndex = (yIndex * image->width + xIndex) * image->channels + c;
              unsigned char pixelValue = imageBytes[pixelIndex];
              sum += pixelValue * weight;
            }
          }
        }

        int pixelIndex = (i * image->width + j) * image->channels + c;
        newImageBytes[pixelIndex] = (unsigned char)(sum);
      }
    }
  }

  memcpy(image->bytes, newImageBytes, image->height * image->width * image->channels * sizeof(unsigned char));
  free(newImageBytes);
}
