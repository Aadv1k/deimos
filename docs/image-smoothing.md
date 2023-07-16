# Image smoothing

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

<div>

<figure><img src=".gitbook/assets/img1-mean-9.png" alt=""><figcaption><p>Mean filter; Sigma 3, Kernel 9</p></figcaption></figure>

 

<figure><img src=".gitbook/assets/img1.jpg" alt=""><figcaption><p>Original</p></figcaption></figure>

</div>

And that is it. So are we done? is the problem of blurring things solved? No, this filter has some shortcomings, notably.

> it can't distinguish sharper features within the image as relevant, it instead applies a uniform blur over the entire image

Which is why we need the **Gaussian Blur** let's see it further next.
