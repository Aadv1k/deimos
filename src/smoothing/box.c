#include "../include/smoothing/box.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char compute_mean_for_channel(Image * img, int size, int x, int y, int c) {
  int width = img->width;
  int height = img->height;

  int sum = 0;
  int count = 0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (x + j >= width || y + i >= height) continue;
      sum += img->bytes[((y + i) * width + j + x) * img->channels + c];
      count++;
    }
  }

  return (unsigned char)(sum / count);
}

void cv_apply_box_filter(Image * img, int kernSize) {
  int width = img->width;
  int height = img->height;
  int ch = img->channels;

  unsigned char* tempBytes = (unsigned char*)malloc(width * height * ch * sizeof(unsigned char));

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char R = compute_mean_for_channel(img, kernSize, j, i, 0);
      unsigned char G = compute_mean_for_channel(img, kernSize, j, i, 1);
      unsigned char B = compute_mean_for_channel(img, kernSize, j, i, 2);

      tempBytes[(i * width + j) * ch + 0] = R;
      tempBytes[(i * width + j) * ch + 1] = G;
      tempBytes[(i * width + j) * ch + 2] = B;
    }
  }

  memcpy(img->bytes, tempBytes, width * height * ch * sizeof(unsigned char));
  free(tempBytes);
}
