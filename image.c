#include "./image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

void cv_load_image(Image *image) {
  image->bytes = (unsigned char *)stbi_load(
      image->path, &(image->width), &(image->height), &(image->channels), 0);
  if (image->bytes == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }
}

void cv_write_image(Image *image, const char *name) {
  if (stbi_write_png(name, image->width, image->height, image->channels,
                     image->bytes, 0) == 0) {
    printf("Error writing PNG file.\n");
    exit(1);
  }
}

void cv_free_image(Image *image) { free(image->bytes); }
