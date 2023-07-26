# Scaling 

Often times in digitial image processing there is a need to reduce the size of the image on the disc. The simplest option offered to us is to literally reduce the size of the image, this can be achieved via **scaling**.

Although there is also image compression, which can reduce the space occupied by the image on the disc without reducing it's literal size, this process is rather complex and beyond the scope of what we are doing.

To scale an image down we accept a X and Y scaling factor we use the quotient of these values against the width and height to derive the new "reduced" dimensions. Looping through which, we extrract the corresponding value from the full-size image by multiplying the pixel co-ordinates by the factors. Let's take a look

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

The logic is quite simple, as I said earlier, we loop through each pixel, and to extract the corresponding pixel within the full-size image we multiply the current cordinatees with the factor to give us values that roughly make up the image. the higher the factors, the more "gap" there will we when we are picking out pixels from thee original image, loosing more details as wee go.

## Result

```bash
.\bin\deimos scale --sigma 2 .\data\img1.jpg .\docs\.gitbook\assets\scale-3.jpg
```

<div>

<figure><img src="../.gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>

<figure><img src="../.gitbook/assets/scale-2.jpg" alt=""><figcaption><p>Image scaled down by a factor of 2x2</p></figcaption></figure>

</div>
