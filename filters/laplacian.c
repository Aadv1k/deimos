#include "laplacian.h"
#include "./blur.h"
#include "./box.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void cv_apply_laplacian_filter(Image* img, float sigma, int kernSize) {
  int width = img->width;
  int height = img->height;
  int channels = img->channels;

  float sigma1 = sigma;
  int kernSize1 = kernSize * 1.5 + 1;

  cv_apply_gaussian_blur(img, sigma1, kernSize1);

  Image copiedImage;
  copiedImage.width = width;
  copiedImage.height = height;
  copiedImage.channels = channels;

  size_t dataSize = width * height * channels * sizeof(unsigned char);
  copiedImage.bytes = malloc(dataSize);
  memcpy(copiedImage.bytes, img->bytes, dataSize);

  cv_apply_gaussian_blur(&copiedImage, sigma, kernSize);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int c = 0; c < channels; c++) {
        int index = (i * width + j) * channels + c;
        img->bytes[index] = img->bytes[index] - copiedImage.bytes[index];
      }
    }
  }

  free(copiedImage.bytes);
}
