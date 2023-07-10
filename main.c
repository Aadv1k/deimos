#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

typedef struct {
  unsigned char * bytes;
  const char * path;
  int width;
  int height;
  int channels;
} Image;

void cv_load_image(Image* image) {
  image->bytes = (unsigned char *)stbi_load(image->path, &(image->width), &(image->height), &(image->channels), 0);
  if(image->bytes == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }
}

void cv_free_image(Image * image) {
  free(image->bytes);
}


int main(void) {
  Image img = { .path = "file.png" };
  cv_load_image(&img);

  printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", img.width, img.height, img.channels);

  cv_free_image(&img);
  return 0;
}
