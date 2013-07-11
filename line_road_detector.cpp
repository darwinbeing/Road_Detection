#include "Image.h"
#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <math.h>
#include <list>
#define THETA_R 1
//#define M_PI 3.14159
#define R 1000
// #define R 480

// #define T 181
#define T 361
#define COLOR_OF_LINES 255
#define COLOR_OF_ROAD_BOUNDARY 99

// #define T 640
using namespace std;
// usage: ./h3 pic.pgm output_pic.pgm threshold
 
int main(int argc, char **argv){

	if (argc!=4){ // fix here
		printf("Usage: file1 file2 file3\n", argv[0]);
		return 0;
	}
	Image *im;
	im=new Image;
	assert(im!=0);
	
	if (readImage(im, argv[1])!=0){
		printf("Can't open file %s\n", argv[1]);
		return 0;
	}
  if( argv[3] < 0 )
    printf("Enter positive threshold\n");

  int houghThreshold = atoi(argv[3]); //
  int ROWS = im->getNRows();
  int COLUMNS = im->getNCols();

  int accumulator[R][T];
  int theta = 0;
  int max = 0, ro_max = 0, h_max = 0; 
  int ro, h;
  for( int i = 0; i < R; ++i )
    for( int j = 0; j < T; ++j ){
      accumulator[i][j] = 0;
    }
  // Mr. Hough
  for (int i = 0; i < ROWS; ++i){
    for (int j = 0; j < COLUMNS; ++j){
        if( im->getPixel( i, j ) > COLOR_OF_ROAD_BOUNDARY ){ // tweak this
          for( h = 1; h < T; h++ ){
            // ro = ((i)*cos(((float)h*M_PI/T)-M_PI) - (float)(j)*sin(((float)h*M_PI/T)-M_PI));
            // ro = ((j)*cos(((float)h*M_PI/50)-M_PI) - (float)(i)*sin(((float)h*M_PI/50)-M_PI));
            ro = i * cos(h) + j * sin(h);
            if (ro < R && ro > 0){
              accumulator[ro][h]++;
            }
          }
        }  // end if
      }
    } // end Mr. Hough
  list<int> vv;
  // Detect local maxima
  for( int i = 0; i < R; i++){
    for( int j = 0; j < T ; j++ ){
      vv.push_back(accumulator[i][j]);
      if( max < accumulator[i][j] ){
        max = accumulator[i][j];
        ro_max = i;
        h_max = j;
      }
      if( accumulator[i][j] > houghThreshold ){
        for (int w = 0; w < ROWS; ++w){
          int x1 = w;
          int y1 = (-x1)*(cos((float)j)) / (sin((float)j))  + 
                              (i)/(sin((float)j)); 
            while( y1 < 0 || x1 < 0){
              x1++;
              y1++;
            }
            if( x1 < ROWS && x1 > 0 && y1 < COLUMNS && y1 > 0){
              im->setPixel(x1, y1, COLOR_OF_LINES);
            }
        }
        for (int v = 0; v < COLUMNS; ++v){
          int y1 = v;
          int x1 = (-y1)*(sin((float)j)) / (cos((float)j))  + 
                              (i)/(cos((float)j)); 
          while( x1 < 0 || y1 < 0){
            x1++;
            y1++;
          }
          if( x1 < ROWS && x1 > 0 && y1 < COLUMNS && y1 > 0){
            im->setPixel(x1, y1, COLOR_OF_LINES);
          } 
        } // end for
      }
    }
  }

  printf("max = %d \n", max );

  vv.unique();
  vv.sort();

  printf("\n");
	if (writeImage(im, argv[2])!=0){
		printf("Can't write to file %s\n", argv[2]);
		return 0;
	}
} // end main

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

