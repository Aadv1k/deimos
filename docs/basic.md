# Computer Vision

This folder contains the "how" of this repository, primarily as a reference to myself. Feel free to use this to aid you in your process. 

## Introduction

Computer vision is an umbrella term which encapsulates several complex topics, but to distill it simply, "How a computer sees the world". Any visual data from an image or an video is really a series of pixels, where each pixel would be an RGB value (or HSL, RGBA) where each integer holds a value between 0-255 describing the intensity of the color channel it holds. So with this, it would not be wrong to say that an image is essentially

```
Image {
  Data      = 255, 0, 128
              0, 128, 255
              128, 255, 0 
              64, 192, 128 
              128, 64, 192
  Width     = 30
  Height    = 30
  Channels  = 3
}
```

And through this abstract representation we can essentially describe any image possible (in this case videos would basically be series of images). So to conclude, Computer vision esseentially consists of appllying mathematical transformations on a matrix of integers.

## Scope and Utility

From the clever filters in photoshop to complex real time "spatial" computing (AR/VR), the key to it all is a little bit of math and bit wizardary. Blurring is the pillar of avoiding copyright infrignement and taking dramatic selfies, There are several ways to go about implementing it, the most popular methood however is the **Gaussian Blur**, let's take further look at this concept in the next section.


[NEXT PAGE](./blurring.md)
