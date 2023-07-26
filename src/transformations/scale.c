#include "../include/transformations/scale.h" 
#include <assert.h>
#include <stdlib.h>

void deimos_apply_scaling(Image * img, int factorX, int factorY) {
  int newWidth = img->width / factorX,
      newHeight = img->height / factorY;

    Image* scaled_img = (Image*)malloc(sizeof(Image));
    scaled_img->width = newWidth;
    scaled_img->height = newHeight;
    scaled_img->channels = img->channels;
    scaled_img->bytes = (unsigned char*)malloc(newWidth * newHeight * img->channels);

    for (int i = 0; i < newHeight; i++) {
      for (int j = 0; j < newWidth; j++) {
        for (int c = 0; c < img->channels; c++) {
          int original_x = j * factorX;
          int original_y = i * factorY;

          scaled_img->bytes[(i * newWidth + j) * img->channels + c] = img->bytes[(original_y * img->width + original_x) * img->channels + c];
        }
      }
    }


    free(img->bytes);

    img->width = scaled_img->width;
    img->height = scaled_img->height;
    img->channels = scaled_img->channels;
    img->bytes = scaled_img->bytes;

    free(scaled_img);
}
