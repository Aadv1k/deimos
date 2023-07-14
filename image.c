#include "./image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

#include "./logging.h"

void cv_load_image(Image *image) {
  image->bytes = (unsigned char *)stbi_load(
      image->path, &(image->width), &(image->height), &(image->channels), 0);
  if (image->bytes == NULL) {
    CV_ERROR("unable to load image %s", image->path);
    exit(1);
  }
}

void cv_write_image(Image *image, const char *name) {
  if (stbi_write_png(name, image->width, image->height, image->channels,
                     image->bytes, 0) == 0) {
    CV_ERROR("unable to write PNG file %s", name);
    exit(1);
  }
}

void cv_free_image(Image *image) { free(image->bytes); }
