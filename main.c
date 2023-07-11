#include <stdio.h>
#include <string.h>
#include "./filters/blur.h"
#include "./image.h"

void usage() {
  printf("Usage: cv.c blur [options] [input] [output]\n");
  printf("Options:\n");
  printf("  -s <sigma>    Set the blur sigma value (default: 1.0)\n");
}

int main(int argc, char ** argv) {
  if (argc != 4) {
    usage();
    return 1;
  }

  if (strcmp(argv[1], "blur") != 0) {
    printf("Error: Invalid command. Only 'blur' command is supported.\n");
    usage();
    return 1;
  }

  const char* input_path = argv[2];
  const char* output_path = argv[3];

  Image img = { .path = input_path };
  cv_load_image(&img);

  cv_apply_gaussian_blur(&img, 1.0);  // Default sigma value, can be modified with -s option

  cv_write_image(&img, output_path);

  cv_free_image(&img);
  return 0;
}
