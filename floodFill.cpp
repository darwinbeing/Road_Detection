#include "Image.h"
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
/***********************
 * function prototypes *
 ***********************/
void floodFill4(Image *im, int x, int y, int newLabel, int oldLabel);
void convert_to_binary (Image *IM);
////////////////////////////////
int main(int argc, char **argv){
	if (argc!=3){
		printf("Usage: file1 file2\n", argv[0]);
		return 0;
	}
	Image *im;
	im=new Image;
	assert(im!=0);
	
	if (readImage(im, argv[1])!=0){
		printf("Can't open file %s\n", argv[1]);
		return 0;
	}
	convert_to_binary(im);
  int xx = im->getNCols( );
  int yy = im->getNRows( )-1;
  line( im, 0, 0, 0, xx, 255 );
  line( im, 1, xx-1, yy-1, xx-1, 255 ); 
  line( im, yy, xx, yy, 0, 255 );
  line( im, yy, 0, 0, 0, 255 );
  // line( im, yy-3, xx/2, 2, 2, 255 );

  floodFill4(im, yy-3, xx/3, 255, 0);
  floodFill4(im, yy-3, xx/1.5, 255, 0);
//  line (im, 240,410,20,50,6);
	if (writeImage(im, argv[2])!=0){
		printf("Can't write to file %s\n", argv[2]);
		return 0;
	}
}

//////////////
void floodFill4(Image *im, int x, int y, int newLabel, int oldLabel) 
{ 
  if( x >= 0 && x < im->getNRows() && 
      y >= 0 && y < im->getNCols() && 
      im->getPixel(x,y) == oldLabel && im->getPixel(x,y) != newLabel
    ){
    im->setPixel(x,y,newLabel); //set color before starting recursion
    
    floodFill4(im, x + 1, y,     newLabel, oldLabel);
    floodFill4(im, x - 1, y,     newLabel, oldLabel);
    floodFill4(im, x,     y + 1, newLabel, oldLabel);
    floodFill4(im, x,     y - 1, newLabel, oldLabel);
  }     
}

void convert_to_binary(Image *IM)
{
  for (int i = 0; i < IM->getNRows(); ++i)
    for (int j = 0; j < IM->getNCols(); ++j){
      if (IM->getPixel(i, j) > 238) // using 240 as threshold
        IM->setPixel(i, j, 255);
      else
        IM->setPixel(i, j, 0);
    }
}