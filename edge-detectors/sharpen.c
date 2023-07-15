#include <stdlib.h>
#include <string.h>
#include "./sharpen.h"

#include "../filters/grayscale.h"
#include "../filters/blur.h"
#include "../image.h"

void cv_apply_sharpening(Image *img, float strength, int kernSize) {
  size_t imgSize = img->width*img->height*img->channels;
  unsigned char * originalImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
  memcpy(originalImage, img->bytes, imgSize * sizeof(unsigned char));

  cv_apply_gaussian_blur(img, strength, kernSize);

  for (int i = 0; i < imgSize; i++) {
    img->bytes[i] = originalImage[i]  + (originalImage[i] - img->bytes[i]) * strength;
  }

  free(originalImage);
}
