# Image Demosaicing
## Goal
Re-constructe the full color image (RGB) from CFA (Color Filter Array) filtered image (gray scale), using [bilinear demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#bilinear-demosaicing-1) and [MHC demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#mhc-demosaicing-1)
## How to run (MacOS terminal):
- Using C++
- 'cat.raw': the CFA filtered image to be re-constructed
- 'output.raw': re-constructed RGB image
- 'bi': [bilinear demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#bilinear-demosaicing-1)
- 'mhc': [MHC demosaicing](https://github.com/J-Yan/Image_Processing_Yan_Jiao/tree/master/Image_Demosaicing#mhc-demosaicing-1)

Step 1:
```
g++ -Wall -std=c++17 Demosaicing.cpp -o custom_name.o
```
Step 2:
###### Bilinear demosaicing:
```
./custom_name.o cat.raw output.raw bi
```
###### MHC demosaicing:
```
./custom_name.o cat.raw output.raw mhc
```

## Methods' introduction
###### Bilinear demosaicing
###### MHC demosaicing
