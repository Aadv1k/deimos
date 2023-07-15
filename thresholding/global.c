#include "./global.h"
#include "../smoothing/grayscale.h"
#include "assert.h"

#define GRAYSCALE_WHITE 255
#define GRAYSCALE_BLACK 0

void cv_apply_global_threshold(Image * img, int threshold) {
  cv_apply_grayscale(img);

  int width = img->width,
      height = img->height,
      ch = img->channels;

  assert(ch == 1 && "The image must be grayscale");

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int pixel_value = img->bytes[(i * width) + j];
      img->bytes[(i * width) + j] = pixel_value >= threshold ? GRAYSCALE_WHITE : GRAYSCALE_BLACK;
    }
  }
}
