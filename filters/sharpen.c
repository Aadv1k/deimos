#include <stdlib.h>
#include <string.h>
#include "./sharpen.h"
#include "./grayscale.h"
#include "./blur.h"
#include "../image.h"

void cv_apply_sharpening(Image *img, float strength) {
  cv_apply_grayscale(img);

  size_t imgSize = img->width*img->height*img->channels;
  unsigned char * originalImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
  memcpy(originalImage, img->bytes, imgSize * sizeof(unsigned char));

  cv_apply_gaussian_blur(img, 3, 9);

  for (int i = 0; i < imgSize; i++) {
    img->bytes[i] = originalImage[i]  + (originalImage[i] - img->bytes[i]) * strength;
  }

  free(originalImage);
}
