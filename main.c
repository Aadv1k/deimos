#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./image.h"

#include "./filters/blur.h"
#include "./filters/grayscale.h"
#include "./filters/median.h"
#include "./filters/sharpen.h"
#include "./filters/bilateral.h"

void usage(const char *caller) {
  printf("Usage:\n");
  printf("\t%s <args> input output\n", caller);
  printf("Examples:\n");
  printf("\t%s --blur --sigma 3.4 input.png output.png\n", caller);
  printf("\t%s --gray input.png output.png\n", caller);
  printf("Options:\n");
  printf("\t--help        print this help message\n");
  printf("\t--blur        apply gaussian blur to the image\n");
  printf("\t--median      apply median filter to the image\n");
  printf("\t--gray        convert image to grayscale\n");
  printf("\t--sharpen     sharpen image via an unsharp mask\n");
  printf("\t--strength    the strength for the sharpening (default 0.5)\n");
  printf("\t--radius      specify the radius for kernel based masks (default 1.0)\n");
}

int main(int argc, char **argv) {
  const char *caller = argv[0];

  if (argc == 1) {
    usage(caller);
    exit(1);
  }

  int enableBlur = 0;
  int enableGrayscale = 0;
  int enableSharpen = 0;
  int enableMedian = 0;
  int enableBilateral = 0;

  int cmdc = 0;
  float blurSigma = 1.0;
  float sharpStrength = 0.5;

  for (int i = 1; i < argc; i++) {
    const char *current = argv[i];

    if (strcmp(current, "--blur") == 0) {
      enableBlur = 1;
      cmdc++;
    } else if (strcmp(current, "--bilateral") == 0)  {
      enableBilateral = 1;
      cmdc++;
    } else if (strcmp(current, "--median") == 0) {
      enableMedian = 1;
      cmdc++;
    } else if (strcmp(current, "--sharpen") == 0) {
      enableSharpen = 1;
      cmdc++;
    } else if (strcmp(current, "--gray") == 0) {
      enableGrayscale = 1;
      cmdc++;
    } else if (strcmp(current, "--radius") == 0) {
      cmdc += 2;

      if (i + 1 < argc) {
        blurSigma = atof(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --radius requires a value.\n");
        exit(1);
      }
    } else if (strcmp(current, "--strength") == 0) {
      cmdc += 2;

      if (i + 1 < argc) {
        sharpStrength = atof(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --strength requires a value.\n");
        exit(1);
      }
    } else {
      usage(caller);
      exit(0);
    }
  }

  if (argc - cmdc <= 2) {
    usage(caller);
    exit(1);
  }

  const char *input_path = argv[argc - 2];
  const char *output_path = argv[argc - 1];

  Image img = {.path = input_path};
  cv_load_image(&img);

  if (enableGrayscale) {
    cv_apply_grayscale(&img);
    printf("Info: applied grayscale\n");
  }

  if (enableBilateral) {
    cv_apply_bilateral_filter(&img, blurSigma);
    printf("Info: applied bilateral filter\n");
  }

  if (enableMedian) {
    cv_apply_median_filter(&img, blurSigma);
    printf("Info: applied median filter\n");
  }

  if (enableSharpen) {
    cv_apply_sharpening(&img, sharpStrength);
    printf("Info: applied sharpen\n");
  }

  if (enableBlur) {
    cv_apply_gaussian_blur(&img, blurSigma, 9);
    printf("Info: applied gaussian blur of intensity %.2f\n", blurSigma);
  }

  cv_write_image(&img, output_path);

  cv_free_image(&img);
  return 0;
}
