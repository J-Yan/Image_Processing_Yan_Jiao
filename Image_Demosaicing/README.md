# Image Demosaicing
## Goal
Re-constructe the full color image (RGB) from CFA (Color Filter Array) filtered image (gray scale), using [bilinear demosaicing]() and [MHC demosaicing]()
## How to run (MacOS terminal):
```
g++ -Wall -std=c++17 Demosaicing.cpp -o custom_name.o
```
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
