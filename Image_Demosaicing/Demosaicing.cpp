// JY569HW1.cpp : Defines the entry point for the console application.


#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//
void Extend(unsigned char *in, unsigned char *out, int extNum, int row, int col){ // row, col -> ori
	// top
	for (int i = 1; i <= extNum; i++) {
		for (int j = 0; j < col; j++) {
			out[(extNum-i)*(col+2*extNum) + j + extNum]=(in[i*col + j]);
			//out[(extNum-i)*(col+2*extNum) + j + extNum]=0;
		}
	}
	// bottom
	for (int i = 1; i <= extNum; i++) {
		for (int j = 0; j < col; j++) {
			out[(row+extNum+i-1)*(col+2*extNum) + j + extNum]=(in[(row-i-1)*col + j]);
		}
	}
	// middle
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			out[(extNum+i)*(col+2*extNum) + (j + extNum)]=in[i*col + j];
		}
	}
	// left
	for (int i = 1; i <= extNum; i++) {
		for (int j = 0; j < col; j++) {
			out[j*(col + 2*extNum) + (extNum - i)]=out[j*(col+extNum*2) + (i + extNum)];
		}
	}
	// right
	for (int i = 1; i <= extNum; i++) {
		for (int j = 0; j < col; j++) {
			out[j*(col + 2*extNum) + (col + extNum- 1 + i)]=out[j*(col+extNum*2) + (col + extNum- 1 - i)];
		}
	}
}

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	int SizeX = 300;
	int SizeY = 390;
  int padding_num = 2;

	// Check for proper syntax
  // method_name: bi -- bilinear
  //              mhc -- Malvar-He-Cutler
	if (argc < 4) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_img.raw output_img.raw method_name [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 5) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[4]);
		// Check if size is specified
		if (argc >= 6) {
			SizeX = atoi(argv[5]);
		}
	}

	// Allocate image data array
  unsigned char Imagedata[SizeX][SizeY][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), SizeX*SizeY*BytesPerPixel, file);
	fclose(file);

  if (strcmp(argv[3], "mhc") == 0) {
    padding_num = 4;
  }

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
  unsigned char Temp[SizeX+padding_num][SizeY+padding_num][BytesPerPixel];
  unsigned char ImagedataOut[SizeX][SizeY][BytesPerPixel*3];
  if (strcmp(argv[3], "bi") == 0) {
    /////////////// extend the image data array, 1px outer /////////////////////////

    Extend(&Imagedata[0][0][0], &Temp[0][0][0], 1, SizeX, SizeY);

  	/////////////////// output image data array //////////////////////////////

  	for (int i=1; i<=SizeX; i++) {
      for (int j=1; j<=SizeY; j++) {
          if ((i+j)%2 == 0) {  // already has green
  					if (i%2 == 1) {
  						ImagedataOut[i-1][j-1][0] = (Temp[i][j-1][0] + Temp[i][j+1][0]) / 2;
  						ImagedataOut[i-1][j-1][1] = Temp[i][j][0];
  						ImagedataOut[i-1][j-1][2] = (Temp[i-1][j][0] + Temp[i+1][j][0]) / 2;
  					}
          	else {
  						ImagedataOut[i-1][j-1][2] = (Temp[i][j-1][0] + Temp[i][j+1][0]) / 2;
  						ImagedataOut[i-1][j-1][1] = Temp[i][j][0];
  						ImagedataOut[i-1][j-1][0] = (Temp[i-1][j][0] + Temp[i+1][j][0]) / 2;
  					}
          }
          else if (i%2 == 1) { // red
            ImagedataOut[i-1][j-1][0] = Temp[i][j][0];
            ImagedataOut[i-1][j-1][1] = (Temp[i][j-1][0] + Temp[i][j+1][0] + Temp[i-1][j][0] + Temp[i+1][j][0]) / 4;
            ImagedataOut[i-1][j-1][2] = (Temp[i-1][j-1][0] + Temp[i+1][j+1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0]) / 4;
          }
          else { // blue
            ImagedataOut[i-1][j-1][0] = (Temp[i-1][j-1][0] + Temp[i+1][j+1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0]) / 4;
            ImagedataOut[i-1][j-1][1] = (Temp[i-1][j][0] + Temp[i+1][j][0] + Temp[i][j-1][0] + Temp[i][j+1][0]) / 4;
            ImagedataOut[i-1][j-1][2] = Temp[i][j][0];
          }
      }
    }
  }
  else if (strcmp(argv[3], "mhc") == 0) {
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

  	/////////////// extend the image data array, 2px outer /////////////////////////

    unsigned char Temp[SizeX+4][SizeY+4][BytesPerPixel];
  	Extend(&Imagedata[0][0][0], &Temp[0][0][0], 2, SizeX, SizeY);
  	//----------------- output image data array
  	int red,green,blue;
  	for (int i=2; i<=SizeX+1; i++) {
      for (int j=2; j<=SizeY+1; j++) {
          if ((i+j)%2 == 0) {  // already has green
  					if ((i%2) == 0) {
  						red = ((Temp[i][j-1][0] + Temp[i][j+1][0]) * 4 + Temp[i][j][0] * 5
  																				- (Temp[i-1][j-1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0] + Temp[i+1][j+1][0] + Temp[i][j-2][0] + Temp[i][j+2][0])
  																				+ (Temp[i-2][j][0] + Temp[i+2][j][0]) / 2) / 8;
  	          green = Temp[i][j][0];
  	          blue = ((Temp[i-1][j][0] + Temp[i+1][j][0]) * 4 +
  																				Temp[i][j][0] * 5 - (Temp[i-1][j-1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0] + Temp[i+1][j+1][0] +
  																				Temp[i-2][j][0] + Temp[i+2][j][0]) + (Temp[i][j-2][0] + Temp[i][j+2][0]) / 2) / 8;
  					}
            else {
  						blue = ((Temp[i][j-1][0] + Temp[i][j+1][0]) * 4 +
  																				Temp[i][j][0] * 5 - (Temp[i-1][j-1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0] + Temp[i+1][j+1][0] +
  																				Temp[i][j-2][0] + Temp[i][j+2][0]) + (Temp[i-2][j][0] + Temp[i+2][j][0]) / 2) / 8;
  	          green = Temp[i][j][0];
  	          red = ((Temp[i-1][j][0] + Temp[i+1][j][0]) * 4 +
  																				Temp[i][j][0] * 5 - (Temp[i-1][j-1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0] + Temp[i+1][j+1][0] +
  																				Temp[i-2][j][0] + Temp[i+2][j][0]) + (Temp[i][j-2][0] + Temp[i][j+2][0]) / 2) / 8;
  					}
          }
          else if (i%2 == 0) { // red
            red = Temp[i][j][0];//cout << (int)Temp[i][j][0]<<" "<<(int)Imagedata[i-2][j-2][0]<<endl;
            green = ((Temp[i][j-1][0] + Temp[i][j+1][0] + Temp[i-1][j][0] + Temp[i+1][j][0]) * 2 +
  																			Temp[i][j][0] * 4 - (Temp[i][j-2][0] + Temp[i][j+2][0] + Temp[i-2][j][0] + Temp[i+2][j][0])) / 8;
            blue = ((Temp[i-1][j-1][0] + Temp[i+1][j+1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0]) * 2 +
  																			Temp[i][j][0] * 6 - (Temp[i][j-2][0] + Temp[i][j+2][0] + Temp[i-2][j][0] + Temp[i+2][j][0]) * 3 / 2) / 8;
          }
          else { // blue
            red = ((Temp[i-1][j-1][0] + Temp[i+1][j+1][0] + Temp[i-1][j+1][0] + Temp[i+1][j-1][0]) * 2 +
  																			Temp[i][j][0] * 6 - (Temp[i][j-2][0] + Temp[i][j+2][0] + Temp[i-2][j][0] + Temp[i+2][j][0]) * 3 / 2) / 8;;
            green = ((Temp[i][j-1][0] + Temp[i][j+1][0] + Temp[i-1][j][0] + Temp[i+1][j][0]) * 2 +
  																			Temp[i][j][0] * 4 - (Temp[i][j-2][0] + Temp[i][j+2][0] + Temp[i-2][j][0] + Temp[i+2][j][0])) / 8;
            blue = Temp[i][j][0];
          }


  					if (red > 255) {
  						red = 255;
  					}
  					if (red < 0) {
  						red = 0;
  					}
  					if (green > 255) {
  						green = 255;
  					}
  					if (green < 0) {
  						green = 0;
  					}
  					if (blue > 255) {
  						blue = 255;
  					}
  					if (blue < 0) {
  						blue = 0;
  					}

  					ImagedataOut[i-2][j-2][0] = red;
  					ImagedataOut[i-2][j-2][1] = green;
  					ImagedataOut[i-2][j-2][2] = blue;

      }
    }
  }

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataOut, sizeof(unsigned char), SizeX*SizeY*BytesPerPixel*3, file);
	fclose(file);

  return 0;
}
