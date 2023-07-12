#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./image.h"

#include "./filters/blur.h"
#include "./filters/grayscale.h"
#include "./filters/sharpen.h"

void usage(const char * caller) {
  printf("Usage:\n");
  printf("\t%s <args> input output\n", caller);
  printf("Examples:\n");
  printf("\t%s --blur --sigma 3.4 input.png output.png\n", caller);
  printf("\t%s --gray input.png output.png\n", caller);
  printf("Options:\n");
  printf("\t--blur     apply gaussian blur to the image\n");
  printf("\t--gray     convert image to grayscale\n");
  printf("\t--sigma    specify the sigma for the blur (default 1.0)\n");
}

int main(int argc, char ** argv) {
    const char * caller = argv[0];

  if (argc == 1) {
    usage(caller);
    exit(1);
  }

  int enableBlur = 0;
  int enableGrayscale = 0;
  int enableSharpen = 0;
  int cmdc = 0;
  float blurSigma  = 1.0;

    for (int i = 1; i < argc; i++) {
        const char* current = argv[i];

        if (strcmp(current, "--blur") == 0) {
            enableBlur = 1;
            cmdc++;
        } else if (strcmp(current, "--sharpen") == 0) {
            enableSharpen = 1;
            cmdc++;
        } else if (strcmp(current, "--gray") == 0) {
            enableGrayscale = 1;
            cmdc++;
              } else if (strcmp(current, "--sigma") == 0) {
            cmdc+=2;

            if (i + 1 < argc) {
                blurSigma = atof(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: --sigma requires a value.\n");
                exit(1);
            }
        }
  }

  if (argc - cmdc <= 2) {
    usage(caller);
    exit(1);
  }

  const char* input_path = argv[argc - 2];
  const char* output_path = argv[argc - 1];

  Image img = { .path = input_path };
  cv_load_image(&img);

  if (enableGrayscale)  {
    cv_apply_grayscale(&img);
    printf("Info: applied grayscale\n");
  }

  if (enableSharpen)  {
    cv_apply_sharpening(&img, 0.5);
    printf("Info: applied sharpen\n");
  }


  if (enableBlur)  {
    cv_apply_gaussian_blur(&img, blurSigma, 9);
    printf("Info: applied gaussian blur of intensity %.2f\n", blurSigma);
  }


  cv_write_image(&img, output_path);

  cv_free_image(&img);
  return 0;
}
