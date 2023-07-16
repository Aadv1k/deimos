---
description: What is computer vision? what is it's scope and utility?
---

# Introduction

### What is Computer Vision?

Computer vision is an umbrella term that encapsulates several complex topics, but to distill it simply, it is about "how a computer sees the world" Let's try to further understand the medium in which this computer does so.

Any visual data, whether from an image or a video, is essentially a series of pixels, where each pixel represents an RGB value (or HSL, RGBA), and each integer holds a value between 0 and 255, describing the intensity of the color channel it represents. So with this, it would not be wrong to say that an image is an array or list of integer values, and computer vision involves processing and analyzing this list to make sense of the visual information it contains.

```c
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

Through this abstract representation we can essentially describe any image possible (in this case videos would basically be series of images). So then Computer vision essentially essentially becomes application of mathematical transformations on an array of integers.

CV has it's own cool and useful application; From the clever filters in Photoshop to complex real time "spatial" computing (AR/VR), the key to it all is a little bit of math and bit wizardry. As early as 60s humans have been trying to figure out how they can apply computation to visual data. In my opinion the field really took off around 2009 on google's introduction of robot cars, which ultimately led to the self-driving car master-race which truly test our capabilities of image processing and machine learning.

sticking to the theme of [_KISS (Keep it simple, stupid!)_](https://en.wikipedia.org/wiki/KISS\_principle) Let's see _how_ behind this tech
