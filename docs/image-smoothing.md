# Image smoothing

## What is image smoothing?

Previously we learnt about f**ilters,** smoothing can define any filter which serves to reduce the amount of extraneous information or **noise** within the image, such functions come in various shapes and forms, with each having their own pros and cons. Smoothing functions all work in a similar manner, they derive some kind of average or weighted value from the set of pixels within the kernel area and set the current pixel to that value.

So let's take a look at such filters and how they are implemented

### Box (Mean) Filter

But what the heck is Mean filter? will it tell me to shut up? Well no. You might be familiar with the mathematical mean, which looks like so

$$
\bar{x} = \frac{1}{n} \sum_{i=1}^{n} x_i
$$

or a less obtuse way to imply the same

```
SUM(array)/LENGTH(array)
```

Mean filter works by assigning the current pixel to the mean of all it's surrounding pixels, which effectively results in a blurred effect.

The Box (Mean) filter is implemented at [smoothing/box.c](../smoothing/box.c#L24), Let's take a deeper look at it.

```c
void cv_apply_box_filter(Image * img, int kernSize) {
  /* ... */

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char R = compute_mean_for_channel(img, kernSize, j, i, 0);
      unsigned char G = compute_mean_for_channel(img, kernSize, j, i, 1);
      unsigned char B = compute_mean_for_channel(img, kernSize, j, i, 2);

      tempBytes[(i * width + j) * ch + 0] = R;
      tempBytes[(i * width + j) * ch + 1] = G;
      tempBytes[(i * width + j) * ch + 2] = B;
    }
  }

  /* ... */
}
```

As expected we loop through every pixel, more specifically every channel within the image, and for each we compute their mean, we can do via a simple function

```c
unsigned char compute_mean_for_channel(Image * img, int size, int x, int y, int c) {

  /* ... */

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      sum += img->bytes[((y + i) * img->width + j + x) * img->channels + c];
      count++;
    }
  }

  /* ... */

  return sum / count;
}
```

My apologies if this code isn't very clear, all we doing is for the index provided, we sum up the next N values to it's right and below (where N = kernSize = size).&#x20;

<pre class="language-bash"><code class="lang-bash"><strong>.\bin\cv.exe  --mean --kernel 9 .\data\img1.jpg .\img1-mean-9.png
</strong></code></pre>

<div>

<figure><img src=".gitbook/assets/img1-mean-9.png" alt=""><figcaption><p>Mean filter; Kernel size 9x9</p></figcaption></figure>

 

<figure><img src=".gitbook/assets/img1.jpg" alt=""><figcaption><p>Original</p></figcaption></figure>

</div>

And that is it. So are we done? is the problem of blurring things solved? No, this filter has some shortcomings, notably.

> it can't distinguish sharper features within the image as relevant, it instead applies a uniform blur over the entire image

Which is why we need the **Gaussian Blur** let's see it further next.

### Gaussian Blur

The Gaussian blur is one of the most popular blurring algorithms, where even applications like Photoshop and Gimp use it as their primary implementation. The Gaussian blur applies the  **Gaussian** or **Normal distribution** which is a function in statistics which distributes values given a `N` across a bell curve, over the pixel values contained within the kernel.&#x20;



$$
f(x) = \frac{1}{\sigma \sqrt{2\pi}} \cdot e^{-\frac{(x - \mu)^2}{2\sigma^2}}
$$

yet again let's unpack this

```
1/SIGMA*SQRT(2*PI) *
EXP^(-(x-MEAN)^2/2 * SIGMA ^2
```

What this function is essentially doing is giving us some value which is contained within a "bell curve" this curve is determined by the  SIGMA and the MEAN. If this sounds too complicated, it's because it is, so let's jump into the code to see what's going on.&#x20;

The Gaussian filter is implemented at [smoothing/blur.c](https://stackedit.io/\[https:/github.com/aadv1k/cv.c/tree/main/smoothing/blur.c]\(https://github.com/aadv1k/cv.c/tree/main/smoothing/blur.c\)) Let's take a deeper look at it.

```c
void cv_apply_gaussian_blur(Image *image, float sigma, int size) {
  /* ... */
  cv_compute_gaussian_kernel(&kernel, sigma, SIZE);

  for (int i = 0; i < image->height; i++) {
    for (int j = 0; j < image->width; j++) {
      for (int c = 0; c < image->channels; c++) {
        for (int k = 0; k < SIZE; k++) {
          for (int l = 0; l < SIZE; l++) {
            /* ... */

            float weight = kernel[k][l];
            int pixelIndex = (yIndex * image->width + xIndex) * image->channels + c;
            unsigned char pixelValue = imageBytes[pixelIndex];

            sum += pixelValue * weight;
            sumWeight += weight;
          }
        }

        int pixelIndex = (i * image->width + j) * image->channels + c;
        newImageBytes[pixelIndex] = (unsigned char)(sum / sumWeight);
      }
    }
  }

  /* ... */
}

```

Stay with me here - We have a kernel of `N` size, we go through each cell of the kernel and assign a value, we compute this value from `sigma` modifer along with the X, and Y co-ordinates of the pixel.&#x20;

We then multiply the kernels's value from the neighbours of the current pixel. After this point the process is similarr to the **Mean filter** where we sum all the (weighted) values that come within kernel bounds and divide them. That produces the following output

```sh
.\bin\cv --blur --kernel 9 --sigma 3 .\data\img1.jpg .\img1-gaussian-3-9.png
```

<div>

<figure><img src=".gitbook/assets/img1.jpg" alt=""><figcaption><p>Original image</p></figcaption></figure>

 

<figure><img src=".gitbook/assets/img1-gaussian-3-9.png" alt=""><figcaption><p>Gaussian Blur of Sigma 3, Kernel 9</p></figcaption></figure>

</div>

The Gaussian Blur is similar to the Box or Mean filter except a `sigma` modifier allows us to control how "sharp" the blur is.
