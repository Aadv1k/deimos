# Scaling 

Digital image processing often involves the need to reduce the size of images stored on disk, and there are two primary methods for achieving this: **scaling** and image compression. Scaling is a straightforward technique that directly reduces the image's dimensions. On the other hand, image compression utilizes advanced algorithms to decrease the space occupied by the image while preserving most of its quality. However, the intricacies of these algorithms are beyond the scope of our current discussion

To scale an image down, we take X and Y scaling factors, and using their quotients against the width and height, we derive the new "reduced" dimensions. By looping through these dimensions, we extract corresponding values from the full-size image, multiplying the pixel coordinates by the scaling factors. Let's take a closer look.


## Implementation

implementation can be found at [src/transformations/scale.c](../../src/transformations/scale.c)

```c
void deimos_apply_scaling(Image * img, int factorX, int factorY) {
  int newWidth = img->width / factorX,
      newHeight = img->height / factorY;

    /* ... */

    for (int i = 0; i < newHeight; i++) {
      for (int j = 0; j < newWidth; j++) {
        for (int c = 0; c < img->channels; c++) {

          int original_x = j * factorX;
          int original_y = i * factorY;

          scaled_img->bytes[(i * newWidth + j) * img->channels + c] = img->bytes[(original_y * img->width + original_x) * img->channels + c];
        }
      }
    }
  
  /* ... */
}
```

In the image scaling process, we iterate through each pixel of the smaller image. To extract the pixel value from the original image, we multiply the coordinates of the new image pixel by the scaling factor. This approach works because it essentially involves 'skipping' pixels in between, resulting in a shorter image at the expense of losing some details. If you think about it, a scaling factor of 2 means we are skipping every other pixel in the image.

## Result

```bash
.\bin\deimos scale --sigma 2 .\data\img1.jpg .\docs\.gitbook\assets\scale-3.jpg
```

> **NOTE:**
> the `sigma` above is just the scaling factor 


<div>

<figure><img src="../.gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>

<figure><img src="../.gitbook/assets/scale-2.jpg" alt=""><figcaption><p>Image scaled down by a factor of 2x2</p></figcaption></figure>

</div>
