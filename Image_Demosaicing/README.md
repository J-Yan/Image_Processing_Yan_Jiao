# Image Demosaicing
## Goal
Re-constructe the full color image (RGB) from CFA (Color Filter Array) filtered image (gray scale), using [bilinear demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#bilinear-demosaicing-1) and [MHC demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#mhc-demosaicing-1)
## How to run (MacOS terminal):
- Using C++
- 'cat.raw': the CFA filtered image to be re-constructed
- 'output.raw': re-constructed RGB output image
- 'bi': [bilinear demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#bilinear-demosaicing-1)
- 'mhc': [MHC demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#mhc-demosaicing-1)

Step 1:
```
g++ -Wall -std=c++17 Demosaicing.cpp -o custom_name.o
```
Step 2:
###### [Bilinear demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#bilinear-demosaicing-1):
```
./custom_name.o cat.raw output.raw bi
```
###### [MHC demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#mhc-demosaicing-1):
```
./custom_name.o cat.raw output.raw mhc
```

## Methods' introduction
###### Bilinear demosaicing
To capture color images, digital camera sensors are usually arranged in form of a color filter array (CFA), called the Bayer array.
Since each sensor at a pixel location only captures one of the three primary colors (R, G, B), the other two colors have to be re-constructed based on their neighbor pixel average values to obtain the full color.

###### MHC demosaicing
Similar with bilinear demosacing, adding a 2nd-order cross-channel correction term to the basic bilinear demosaicing result. Beacaue taking more neighbour information to decide the center pixel value, the re-constructed image will have less error from the original image.

## Reference Images
All images could be found on http://sipi.usc.edu/database/ or http://images.google.com/.
