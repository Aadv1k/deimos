Convolution is smarter way to describe a "function that does some modifications to a set of integers", in our context this function primarily consists of the following :-

- Kernel: a grid which serves to group a particualr section of a image for a convolution. Think of it as a **stencil** where we place this stencil (usually centered) on a pixel and make a note of all the values that it contains.

- Convolution: the modifcation which has to be made to the integers within the kernel, it can be as simple as incrementing each integer by one.

To re-iterate on the above, the kernel will localize a set of pixels the convolution will be applied on. Let's understand this idea in the context of implementing a **Mean filter**.


## Box (or Mean) filter

Is a simple convolution function which iterates over each pixel of image set and based on it's size derives the mean of all the sorrounding neighbours. 

```
μ = (1/n) * Σ(xi)
```

or

```
MEAN = SUM(values)/LEN(values)
```

Take a look at [filters/box.c](../filters/box.c) where this function has been implemented.


```c
void cv_apply_box_filter(Image * img, int kernSize);
```

Here the `kernSize` defines the area of the kernel, this value will define how blurred our image is. Lower `kernSize` will lead to a less blurred image. Another thing to note, if the image size is larger the `kernSize` must also be higher otherwise the effect will be less noticable.

[PREVIOUS PAGE](./basic.md)
