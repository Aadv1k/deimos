#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./sharpen.h"

#include "../smoothing/grayscale.h"
#include "../smoothing/blur.h"
#include "../image.h"

void cv_apply_sharpening(Image *img, float strength, int kernSize) {

  cv_apply_grayscale(img);

  size_t imgSize = img->width * img->height * img->channels;
  unsigned char *originalImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
  memcpy(originalImage, img->bytes, imgSize * sizeof(unsigned char));

  cv_apply_gaussian_blur(img, strength, kernSize);

  unsigned char *blurredImage = (unsigned char *)malloc(imgSize * sizeof(unsigned char));
  memcpy(blurredImage, img->bytes, imgSize * sizeof(unsigned char));


  for (size_t i = 0; i < imgSize; i++) {
    img->bytes[i] = originalImage[i] + (originalImage[i] - blurredImage[i]) * strength;
  }

  free(originalImage);
  free(blurredImage);
}
