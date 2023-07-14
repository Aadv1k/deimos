#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./image.h"

#include "./filters/blur.h"
#include "./filters/grayscale.h"
#include "./filters/median.h"
#include "./filters/sharpen.h"
#include "./filters/bilateral.h"
#include "./filters/box.h"
#include "./filters/laplacian.h"

#ifdef _WIN32
    #define CV_WARN(...) printf("\033[33m[WARNING] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_INFO(...) printf("\033[36m[INFO] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_ERROR(...) printf("\033[31m[ERROR] "); printf(__VA_ARGS__); printf("\033[0m\n")
#else
    #define CV_WARN(...) printf("\033[33m[WARNING] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_INFO(...) printf("\033[36m[INFO] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_ERROR(...) printf("\033[31m[ERROR] "); printf(__VA_ARGS__); printf("\033[0m\n")
#endif

void usage(const char *caller) {
  printf("Usage:\n");
  printf("\t%s <args> input output\n", caller);
  printf("Examples:\n");
  printf("\t%s --blur --sigma 3.4 --kernel 5 input.png output.png\n", caller);
  printf("\t%s --gray input.png output.png\n", caller);
  printf("\t%s --median --kernel 3 input.png output.png\n", caller);
  printf("\t%s --sharpen --sigma 0.6 --kernel 3 input.png output.png\n", caller);
  printf("Options:\n");
  printf("\t--help           print this help message\n");
  printf("\t--blur           apply gaussian blur to the image\n");
  printf("\t--median         apply median filter to the image\n");
  printf("\t--bilateral      apply bilateral filter to the image\n");
  printf("\t--box            apply box filter onto the image\n");
  printf("\t--laplacian      apply laplacian filter onto the image\n");
  printf("\t--gray           convert image to grayscale\n");
  printf("\t--sharpen        sharpen image via an unsharp mask\n");
  printf("\t--sigma          specify the sigma for the convolutions\n");
  printf("\t--radius         define the kernel size for convolutions (if applicable)\n");
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
  int enableBox = 0;
  int enableLaplacian = 0;

  int cmdc = 0;

  float sigma = 1.0;
  int kernelSize = 3;

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
    } else if (strcmp(current, "--box") == 0) {
      enableBox = 1;
      cmdc++;
    } else if (strcmp(current, "--laplacian") == 0) {
      enableLaplacian = 1;
      cmdc++;
    } else if (strcmp(current, "--sharpen") == 0) {
      enableSharpen = 1;
      cmdc++;
    } else if (strcmp(current, "--gray") == 0) {
      enableGrayscale = 1;
      cmdc++;
    } else if (strcmp(current, "--sigma") == 0) {
      cmdc += 2;
      if (i + 1 < argc) {
        sigma = atof(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --radius requires a value.\n");
        exit(1);
      }
    } else if (strcmp(current, "--kernel") == 0) {
      cmdc += 2;

      if (i + 1 < argc) {
        kernelSize = atoi(argv[i + 1]);
        i++;
      } else {
        fprintf(stderr, "Error: --strength requires a value.\n");
        exit(1);
      }
    } else if (strcmp(current, "--help") == 0) {
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
    CV_INFO("converting image to grayscale");
    cv_apply_grayscale(&img);
  }

  if (enableLaplacian) {
    CV_INFO("applying Laplacian filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_laplacian_filter(&img, sigma, kernelSize);
  }

  if (enableBilateral) {
    //int kernSize = floor(sigma / 2.5);
    CV_INFO("applying bilateral filter of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_bilateral_filter(&img, sigma, kernelSize);
  }

  if (enableBox) {
    //int kernSize = floor(sigma / 2.5);
    CV_INFO("applying box filter of kernel size %d", kernelSize);
    cv_apply_box_filter(&img, kernelSize);
  }


  if (enableMedian) {
    CV_INFO("applying median filter of kernel size %d", kernelSize);
    cv_apply_median_filter(&img, kernelSize);
  }

  if (enableSharpen) {
    //int kernelSize = ceil(sharpStrength) * 2 + 1;
    CV_INFO("applying sharpening of strength %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_sharpening(&img, sigma, kernelSize);
  }

  if (enableBlur) {
    //int kernelSize = ceil(sigma*2 + 1);
    CV_INFO("applying gaussian blur of intensity %.2f, kernel size %d", sigma, kernelSize);
    cv_apply_gaussian_blur(&img, sigma, kernelSize);
  }

  cv_write_image(&img, output_path);

  cv_free_image(&img);
  return 0;
}
