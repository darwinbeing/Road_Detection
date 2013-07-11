#include "Image.h"
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#define REMOVETHRESHOLD1 60
/***********************
 * function prototypes *
 ***********************/
void fillToTheTop( Image *im2, int x );
////////////////////////////////
int main(int argc, char **argv){

  Image *im;
  im=new Image;
  assert(im!=0);
  
  if (readImage(im, argv[1])!=0){
    printf("Can't open file %s\n", argv[1]);
    return 0;
  }

  for (int i = im->getNRows()-1; i > 0; --i){ // looping
    int count1 = 0;
    for (int j = im->getNCols()-1; j > 0; --j){
      if (im->getPixel(i, j) > 250) 
        count1++;
    }
    if( count1 < REMOVETHRESHOLD1 ){
      fillToTheTop( im, i );
      break;
    }
  }
  if (writeImage(im, argv[2])!=0){
    printf("Can't write to file %s\n", argv[2]);
    return 0;
  }
}
/////////////////////////////////////////
void fillToTheTop( Image *im2, int x )
{
  for( int i = x; x > 0; --x ){
    line( im2, x, 0, x, im2->getNCols( )-1, 0 );
  }
}