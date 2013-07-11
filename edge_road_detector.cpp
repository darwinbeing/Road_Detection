#include "Image.h"
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <math.h>
#define laplacianThreshold 0
// #define sobelThreshold1 500
// usage: ./h1 hough_complex_1.pgm h1_output.pgm
 
// function prototypes
void convert_to_binary (Image *im);
int getLaplacianValue(Image *t, int i, int j);
int getSobel1(Image *t, int i, int j);
int getSobel2(Image *t, int i, int j);
int getLowLeftUpRight(Image *t, int i, int j);
int getLowRightUpLeft(Image *t, int i, int j);

int main(int argc, char **argv){

	if (argc!=4){
		printf("Usage: file1 file2 threshold\n", argv[0]);
		return 0;
	}
	Image *im;
	im=new Image;
	assert(im!=0);
	
	if (readImage(im, argv[1])!=0){
		printf("Can't open file %s\n", argv[1]);
		return 0;
	}

  int sobelThreshold1 = 0;
  if( argv[3] < 0 )
    printf("Please enter positive threshold\n");
  else
    sobelThreshold1 = atoi(argv[3]);

  int newImage[im->getNRows()][im->getNCols()];

  for (int i = 1; i < im->getNRows()-1; ++i){
    for (int j = 1; j < im->getNCols()-1; ++j){
      int color1 = getLowLeftUpRight(im, i, j);
      int color2 = getLowRightUpLeft(im, i, j);      
      int color = sqrt( color1 + color2);
      
      if (color > sobelThreshold1){ //laplacianThreshold){
        // newImage[i][j] = color;
        newImage[i][j] = 100;
      }
    }
  }

  for (int i = 1; i < im->getNRows()-1; ++i)
    for (int j = 1; j < im->getNCols()-1; ++j)
      im->setPixel( i, j, newImage[i][j]);
  

  printf("\n");
	if (writeImage(im, argv[2])!=0){
		printf("Can't write to file %s\n", argv[3]);
		return 0;
	}
}
 /*
 ****************************
 * function implementations *
 ****************************
 */
void convert_to_binary (Image *IM)
{
  for (int i = 0; i < IM->getNRows(); ++i)
    for (int j = 0; j < IM->getNCols(); ++j){
      if (IM->getPixel(i, j) > 210) // using 110 as threshold
        IM->setPixel(i, j, 255);
      else
        IM->setPixel(i, j, 0);
    }
}

int getLaplacianValue(Image *t, int i, int j)
{
  int value = 0;
  value = (         t->getPixel( i-1, j-1 ) / 6  + 
            4 *     t->getPixel( i-1, j   ) / 6 + 
                    t->getPixel( i-1, j+1 ) / 6  + 
            4 *     t->getPixel( i  , j-1 ) / 6  + 
            (-20) * t->getPixel( i  , j   ) / 6  + 
            4 *     t->getPixel( i  , j+1 ) / 6  + 
                    t->getPixel( i+1, j-1 ) / 6  + 
            4 *     t->getPixel( i+1, j   ) / 6  + 
                    t->getPixel( i+1, j+1 ) / 6  );

  return value;
}

int getSobel1(Image *t, int i, int j)
{
  int delta1 = 0;
  delta1 = ((-1) *  t->getPixel( i-1, j-1 ) + 
              0  *  t->getPixel( i-1, j   ) + 
                    t->getPixel( i-1, j+1 ) + 
            (-2) *  t->getPixel( i  , j-1 ) + 
              0  *  t->getPixel( i  , j   ) + 
              2  *  t->getPixel( i  , j+1 ) + 
            (-1) *  t->getPixel( i+1, j-1 ) + 
              0  *  t->getPixel( i+1, j   ) + 
                    t->getPixel( i+1, j+1 ) );
  return (delta1 * delta1); 
}  

int getSobel2(Image *t, int i, int j)
{
  int delta2 = 0;
  delta2 = (        t->getPixel( i-1, j-1 ) + 
              2  *  t->getPixel( i-1, j   ) + 
                    t->getPixel( i-1, j+1 ) + 
              0  *  t->getPixel( i  , j-1 ) + 
              0  *  t->getPixel( i  , j   ) + 
              0  *  t->getPixel( i  , j+1 ) + 
            (-1) *  t->getPixel( i+1, j-1 ) + 
            (-2) *  t->getPixel( i+1, j   ) + 
            (-1) *  t->getPixel( i+1, j+1 ) );
  return (delta2 * delta2);
}


int getLowLeftUpRight(Image *t, int i, int j)
{
  int delta1 = 0;
  delta1 = ((-2) *  t->getPixel( i-1, j-1 ) + 
            (-1) *  t->getPixel( i-1, j   ) + 
              0  *  t->getPixel( i-1, j+1 ) + 
            (-1) *  t->getPixel( i  , j-1 ) + 
              0  *  t->getPixel( i  , j   ) + 
              1  *  t->getPixel( i  , j+1 ) + 
              0  *  t->getPixel( i+1, j-1 ) + 
              1  *  t->getPixel( i+1, j   ) + 
              2  *  t->getPixel( i+1, j+1 ) );
  return (delta1 * delta1); 
}  

int getLowRightUpLeft(Image *t, int i, int j)
{
  int delta2 = 0;
  delta2 = (  0  *  t->getPixel( i-1, j-1 ) + 
              1  *  t->getPixel( i-1, j   ) + 
              2  *  t->getPixel( i-1, j+1 ) + 
            (-1) *  t->getPixel( i  , j-1 ) + 
              0  *  t->getPixel( i  , j   ) + 
              1  *  t->getPixel( i  , j+1 ) + 
            (-2) *  t->getPixel( i+1, j-1 ) + 
            (-1) *  t->getPixel( i+1, j   ) + 
              0  *  t->getPixel( i+1, j+1 ) );
  return (delta2 * delta2);
}
