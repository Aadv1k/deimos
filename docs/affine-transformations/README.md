# Affine transformations

So far, we have been discussing "convolutional" functions, which compute the value of the current pixel from a neighborhood specified by the kernel. Essentially, we apply transformations atop the image, similar to applying a [photographic filter](https://en.wikipedia.org/wiki/Photographic_filter).

Affine transformations, unlike convolutional functions, accept an image and alter the geometry of the image within a 2D or 3D space. This includes but isn't limited to the size, position, and orientation of an image.

For instance, a common example is **scaling**, where we reduce the width and height of the image to a smaller value, essentially reducing the size of the image. This is crucial for generating thumbnails or making an image more space-efficient. 

Let's consider **rotation**. It's a feature omnipresent in almost all image processing frameworks, and for the right reasons. Rotation can help with alignment. Let's go back to our previous example of a self-driving car, often shocks or jolts can cause the camera to tilt, which is problematic since it can potentially cause incorrect calculations for turns; "Aligning" the images helps eliminate this bottle-neck.

The list may go on about similar functions and their use cases. In the sections that follow, we are going to be discussing several of these transformers andd more importantly their implementation.
