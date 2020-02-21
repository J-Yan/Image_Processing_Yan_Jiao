// course project of USC EE 569 Digital Image Processing
// file read and write code templates are originally from course instructor, I modified them to fit my goal
// author (of other codes): Yan Jiao

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

static int Size = 375;

// the value which represents black in the binary image
static const unsigned char I = 255;

// Digital Image Processing, 4th Edition, Table 14.3-1, pp.433,434
// Skeleton, Thin, and Skeletonize Conditional Mark Patterns [M = 1 if hit]
static const unsigned char k_conditional_patterns[][9] = {
// // S 1
// {0,0,I,
// 0,I,0,
// 0,0,0},
// {I,0,0,
// 0,I,0,
// 0,0,0},
// {0,0,0,
// 0,I,0,
// I,0,0},
// {0,0,0,
// 0,I,0,
// 0,0,I},
//
// // S 2
// {0,0,0,
// 0,I,I,
// 0,0,0},
// {0,I,0,
// 0,I,0,
// 0,0,0},
// {0,0,0,
// I,I,0,
// 0,0,0},
// {0,0,0,
// 0,I,0,
// 0,I,0},
//
// // S 3
// {0,0,I,
// 0,I,I,
// 0,0,0},
// {0,I,I,
// 0,I,0,
// 0,0,0},
// {I,I,0,
// 0,I,0,
// 0,0,0},
// {I,0,0,
// I,I,0,
// 0,0,0},
// {0,0,0,
// I,I,0,
// I,0,0},
// {0,0,0,
// 0,I,0,
// I,I,0},
// {0,0,0,
// 0,I,0,
// 0,I,I},
// {0,0,0,
// 0,I,I,
// 0,0,I},

// TK 4
{0,I,0,
0,I,I,
0,0,0},
{0,I,0,
I,I,0,
0,0,0},
{0,0,0,
I,I,0,
0,I,0},
{0,0,0,
0,I,I,
0,I,0},

// STK 4
{0,0,I,
0,I,I,
0,0,I},
{I,I,I,
0,I,0,
0,0,0},
{I,0,0,
I,I,0,
I,0,0},
{0,0,0,
0,I,0,
I,I,I},

// // ST 5
// {I,I,0,
// 0,I,I,
// 0,0,0},
// {0,I,0,
// 0,I,I,
// 0,0,I},
// {0,I,I,
// I,I,0,
// 0,0,0},
// {0,0,I,
// 0,I,I,
// 0,I,0},

// // ST 5
// {0,I,I,
// 0,I,I,
// 0,0,0},
// {I,I,0,
// I,I,0,
// 0,0,0},
// {0,0,0,
// I,I,0,
// I,I,0},
// {0,0,0,
// 0,I,I,
// 0,I,I},
//
// ST 6
// {I,I,0,
// 0,I,I,
// 0,0,I},
// {0,I,I,
// I,I,0,
// I,0,0},

// STK 6
{I,I,I,
0,I,I,
0,0,0},
{0,I,I,
0,I,I,
0,0,I},
{I,I,I,
I,I,0,
0,0,0},
{I,I,0,
I,I,0,
I,0,0},
{I,0,0,
I,I,0,
I,I,0},
{0,0,0,
I,I,0,
I,I,I},
{0,0,0,
0,I,I,
I,I,I},
{0,0,I,
0,I,I,
0,I,I},

// STK 7
{I,I,I,
0,I,I,
0,0,I},
{I,I,I,
I,I,0,
I,0,0},
{I,0,0,
I,I,0,
I,I,I},
{0,0,I,
0,I,I,
I,I,I},

// STK 8
{0,I,I,
0,I,I,
0,I,I},
{I,I,I,
I,I,I,
0,0,0},
{I,I,0,
I,I,0,
I,I,0},
{0,0,0,
I,I,I,
I,I,I},

// STK 9
{I,I,I,
0,I,I,
0,I,I},
{0,I,I,
0,I,I,
I,I,I},
{I,I,I,
I,I,I,
I,0,0},
{I,I,I,
I,I,I,
0,0,I},
{I,I,I,
I,I,0,
I,I,0},
{I,I,0,
I,I,0,
I,I,I},
{I,0,0,
I,I,I,
I,I,I},
{0,0,I,
I,I,I,
I,I,I},

// STK 10
{I,I,I,
0,I,I,
I,I,I},
{I,I,I,
I,I,I,
I,0,I},
{I,I,I,
I,I,0,
I,I,I},
{I,0,I,
I,I,I,
I,I,I},

// K 11
{I,I,I,
I,I,I,
0,I,I},
{I,I,I,
I,I,I,
I,I,0},
{I,I,0,
I,I,I,
I,I,I},
{0,I,I,
I,I,I,
I,I,I},

};

// Digital Image Processing, 3th Edition, Table 14.3-2, p.435
// Skeleton, Thin, and Skeletonize Unconditional Mark Patterns
// [P(M,M0,M1,M2,M3,M4,M5,M6,M7) = 1 if hit]
// A ∪ B ∪ C = 1
// A ∪ B = 1
// D = 0 ∪ 1
static const unsigned char M = 1;
static const unsigned char A = 2;
static const unsigned char B = 3;
static const unsigned char C = 4;
static const unsigned char D = 5;

static const unsigned char k_unconditional_patterns[][9] = {
// spur
{0,0,M,
0,M,0,
0,0,0},

{M,0,0,
0,M,0,
0,0,0},

{0,0,0,
0,M,0,
M,0,0},

{0,0,0,
0,M,0,
0,0,M},

// Single 4-connection
{0,0,0,
0,M,0,
0,M,0},

{0,0,0,
0,M,M,
0,0,0},

{0,0,0,
M,M,0,
0,0,0},

{0,M,0,
0,M,0,
0,0,0},

// L Corner
{0,M,0,
0,M,M,
0,0,0},

{0,0,0,
0,M,M,
0,M,0},

{0,0,0,
M,M,0,
0,M,0},

{0,M,0,
M,M,0,
0,0,0},
// corner cluster
{M,M,D,
M,M,D,
D,D,D},

{D,D,D,
D,M,M,
D,M,M},
// Tee branch
{D,M,D,
M,M,M,
D,D,D},

{D,D,D,
M,M,M,
D,M,D},

{D,M,D,
M,M,D,
D,M,D},

{D,M,D,
D,M,M,
D,M,D},
//Vee branch
{M,D,M,
D,M,D,
A,B,C},

{A,D,M,
B,M,D,
C,D,M},

{A,B,C,
D,M,D,
M,D,M},

{M,D,A,
D,M,B,
M,D,C},

// Diaagonal branch
{D,M,0,
0,M,M,
M,0,D},

{0,M,D,
M,M,0,
D,0,M},

{D,0,M,
M,M,0,
0,M,D},

{M,0,D,
0,M,M,
D,M,0}

};

// table for checking broken lines
static const unsigned char E = 6;
static const unsigned char F = 7;
static const unsigned char G = 8;
static const unsigned char k_bridge[][9] = {

{A,B,C,
0,D,0,
E,F,G},

{A,0,E,
B,D,F,
C,0,G},

{B,A,D,
C,D,0,
D,0,1},

{D,0,1,
A,D,0,
B,C,D},

{1,0,D,
0,D,C,
D,A,B},

{D,C,B,
0,D,A,
1,0,D}
};


// count each set's number of masks
int NumCond = sizeof(k_conditional_patterns)/sizeof(k_conditional_patterns[0]);
int NumUnCond = sizeof(k_unconditional_patterns)/sizeof(k_unconditional_patterns[0]);
int NumBridge = sizeof(k_bridge)/sizeof(k_bridge[0]);

// loops of two skeleton stages
vector<vector<unsigned char>> Skeleton(vector<vector<unsigned char>> IP) {
	unsigned char StageOne[Size][Size];
	unsigned char StageTwo[Size][Size];
	int loopflag = 1;
	while (loopflag == 1) {

		// stage one
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++){
				StageOne[i][j] = 0;
			}
		}
		unsigned char nine[9];
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++){
				if (IP[i][j] == 255) {
					nine[0] = IP[i-1][j-1];
					nine[1] = IP[i-1][j];
					nine[2] = IP[i-1][j+1];
					nine[3] = IP[i][j-1];
					nine[4] = IP[i][j];
					nine[5] = IP[i][j+1];
					nine[6] = IP[i+1][j-1];
					nine[7] = IP[i+1][j];
					nine[8] = IP[i+1][j+1];
					unsigned char flag = 0;
					for (int k = 0; k < NumCond; k++){
						flag = M;
						for (int m = 0; m < 9; m++) {
							if (k_conditional_patterns[k][m] != nine[m]) {
								flag = 0;
								break;
							}
						}
						StageOne[i][j] = flag;
						if (flag == M) {
							break;
						}
					}
				}
			}
		}

		// stage two
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++){
				StageTwo[i][j] = StageOne[i][j];
			}
		}

		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++){
				if (StageOne[i][j] == M) {
					// loop all masks
					nine[0] = StageOne[i-1][j-1];
					nine[1] = StageOne[i-1][j];
					nine[2] = StageOne[i-1][j+1];
					nine[3] = StageOne[i][j-1];
					nine[4] = StageOne[i][j];
					nine[5] = StageOne[i][j+1];
					nine[6] = StageOne[i+1][j-1];
					nine[7] = StageOne[i+1][j];
					nine[8] = StageOne[i+1][j+1];
					unsigned char flag = 0;
					for (int k = 0; k < NumUnCond; k++){
						flag = M;
						unsigned char ABC = 0;
						unsigned char t = 0;
						for (int m = 0; m < 9; m++) {
							if (k_unconditional_patterns[k][m] > 1 && k_unconditional_patterns[k][m] < 5) {
								ABC = 1;
								if (nine[m] == M) {
									t = 1;
								}
							}
							else if (k_unconditional_patterns[k][m] < 2) {
								if (k_unconditional_patterns[k][m] != nine[m]) {
									flag = 0;
								}
							}
						}
						if (ABC!=t || flag != M) {
							StageTwo[i][j] = 0;
						}
						else {
							StageTwo[i][j] = M;
							break;
						}
					}
				}
			}
		}

		// change the hit foreground pixels to background
		// if no hit pixel, 'loopflag' should be '0'
		loopflag = 0;
		for (int i = 0; i < Size; i++) {
			for (int j = 0; j < Size; j++){
				if (StageOne[i][j] == M && StageTwo[i][j] == 0) {
					IP[i][j] = 0;
					loopflag = 1;
				}
			}
		}
	}
	return IP;
}


// bridge function
// check & connect the broken lines after the skeletonizing process
vector<vector<unsigned char>> Bridge(vector<vector<unsigned char>> IP) {
	unsigned char nine[9];
	for (int i = 1; i < Size-1; i++) {
		for (int j = 1; j < Size-1; j++){
			if (IP[i][j] == 0 && (IP[i-1][j-1]==255|| IP[i-1][j]==255|| IP[i-1][j+1]==255|| IP[i][j-1]==255||IP[i][j+1]==255 ||IP[i+1][j-1]==255 || IP[i+1][j]==255|| IP[i+1][j+1]==255)) {
				nine[0] = IP[i-1][j-1];
				nine[1] = IP[i-1][j];
				nine[2] = IP[i-1][j+1];
				nine[3] = IP[i][j-1];
				nine[4] = IP[i][j];
				nine[5] = IP[i][j+1];
				nine[6] = IP[i+1][j-1];
				nine[7] = IP[i+1][j];
				nine[8] = IP[i+1][j+1];

				unsigned char ABC;
				unsigned char EFG;
				unsigned char abc;
				unsigned char efg;
				unsigned char flag;
				for (int k = 0; k < NumBridge; k++){

					ABC = 0;
					abc = 0;
					EFG = 0;
					efg = 0;
					flag = 1;
					for (int m = 0; m < 9; m++) {
						if (k_bridge[k][m] > 1 && k_bridge[k][m] < 5) {
							ABC = 1;
							if (nine[m] == 255) {
								abc = 1;
							}
						}
						else if (k_bridge[k][m] > 5) {
							EFG = 1;
							if (nine[m] == 255) {
								efg = 1;
							}
						}
						else if (k_bridge[k][m] < 2) {
							if (k_bridge[k][m]*255 != nine[m]) {
								flag = 0;
							}
						}
					}
					if (ABC==abc && flag == 1 && EFG==efg) {
						if (EFG == 1) {
							if (! ((nine[0]==255&&(nine[2]==255||nine[6]==255)) || (nine[8]==255&&(nine[6]==255||nine[2]==255)) )) {
								IP[i][j] = 255;
								break;
							}
						}
						else {
							IP[i][j] = 255;
							break;
						}
					}
				}
			}
		}
	}
	return IP;
}

int main(int argc, char *argv[])
{
	// vvv
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 1;
	// ^^^

	// Check for proper syntax
	if (argc < 9) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image1.raw input_image2.raw input_image3.raw input_image4.raw output_image.raw output_imag2.raw output_image3.raw output_image4.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Allocate image data array
  	unsigned char Image1[Size][Size][BytesPerPixel];
	unsigned char Image2[Size][Size][BytesPerPixel];
	unsigned char Image3[Size][Size][BytesPerPixel];
	unsigned char Image4[Size][Size][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	fread(Image1, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[2], "rb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fread(Image2, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[3], "rb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fread(Image3, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[4], "rb"))) {
		cout << "Cannot open file: " << argv[4] << endl;
		exit(1);
	}
	fread(Image4, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	unsigned char ImageOut1[Size][Size][BytesPerPixel];
	unsigned char ImageOut2[Size][Size][BytesPerPixel];
	unsigned char ImageOut3[Size][Size][BytesPerPixel];
	unsigned char ImageOut4[Size][Size][BytesPerPixel];

	vector<vector<unsigned char>> I1(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I2(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I3(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I4(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I1O(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I2O(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I3O(Size,vector<unsigned char>(Size, 0));
	vector<vector<unsigned char>> I4O(Size,vector<unsigned char>(Size, 0));

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			I1[i][j] = Image1[i][j][0];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			I2[i][j] = Image2[i][j][0];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			I3[i][j] = Image3[i][j][0];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			I4[i][j] = Image4[i][j][0];
		}
	}

	// skeletonize & bridge the image
	I1O = Bridge(Skeleton(I1));
	I2O = Bridge(Skeleton(I2));
	I3O = Bridge(Skeleton(I3));
	I4O = Bridge(Skeleton(I4));
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			ImageOut1[i][j][0] = I1O[i][j];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			ImageOut2[i][j][0] = I2O[i][j];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			ImageOut3[i][j][0] = I3O[i][j];
		}
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++){
			ImageOut4[i][j][0] = I4O[i][j];
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	if (!(file = fopen(argv[5], "wb"))) {
		cout << "Cannot open file: " << argv[5] << endl;
		exit(1);
	}
	fwrite(ImageOut1, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[6], "wb"))) {
		cout << "Cannot open file: " << argv[6] << endl;
		exit(1);
	}
	fwrite(ImageOut2, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[7], "wb"))) {
		cout << "Cannot open file: " << argv[7] << endl;
		exit(1);
	}
	fwrite(ImageOut3, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);
	if (!(file = fopen(argv[8], "wb"))) {
		cout << "Cannot open file: " << argv[8] << endl;
		exit(1);
	}
	fwrite(ImageOut4, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

    	return 0;
}
