#include "../include/transformations/rotate.h"

#include <assert.h>

void deimos_apply_rotation(Image * img, RotationDegree deg) {
  switch (deg) {
    case (DEG_180):
      (void)img;
      assert(0 && "Not implemente");
      break;
    default:
      assert(0 && "Not a valid degree");
  }
}
