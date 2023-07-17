# Image smoothing

## What is image smoothing?

Previously we learnt about f**ilters,** smoothing can define any filter which serves to reduce the amount of extraneous information or **noise** within the image, such functions come in various shapes and forms, with each having their own pros and cons. Smoothing functions all work in a similar manner, they derive some kind of average or weighted value from the set of pixels within the kernel area and set the current pixel to that value.

So, let's take a look at how they are implemented.

###
