#include <stdlib.h>
#include <string.h>

#include "../include/smoothing/grayscale.h"

void cv_apply_grayscale(Image * img) {
  if (img->channels == 1) return;

   unsigned char * grayBytes = (unsigned char *)malloc(img->width * img->height * sizeof(unsigned char));

  for (int i = 0, j = 0; i < img->width * img->height * img->channels; i+=img->channels, j++) {
    const unsigned char R = img->bytes[i],
                        G = img->bytes[i + 1],
                        B = img->bytes[i + 2];

    const unsigned char grayscale = (unsigned char)((0.3 * R) + (0.59 * G) + (0.11 * B));
    grayBytes[j] = grayscale;
  }

  memcpy(img->bytes, grayBytes, img->width*img->height*sizeof(unsigned char));
  img->channels = 1;

  free(grayBytes);
}
