Created by:     Vitaliy Matiyash
Class:          CSCI 493.69 Computational Vision
Professor:      Ioannis Stamos
Date:           May 2013
Final Project:  Road Detection Algorithm
---------------------------------------------------------------------
> DESCRIPTION:  I have implemented an algorithm for road detection 
                from single image.

                Algorithm proceeds in the following steps (which are
                implemented as separate programs):
                1. Detect edges.
                2. Perform Hough Transform for line detection. 
                      This will detect boundaries of the road.
                3. Perform Flood Fill algorithm in 2 points:
                      left 1/3 of image
                      right 1/3 of image
                4. Remove the unnecesary lines in upper part of image
                   that do not belong to the road.
                      

---------------------------------------------------------------------
> NOTES:
          To see the obtained results in a nicely arranged way go to 
          folder "results" and view the experimentally obtained images

          Algorithm needs some tweeking if new images were to be
          used for input. For example, threshold parameters for edge
          detector or Hough Transform.

          I have decided to break program into separate files that
          are compiled and run separately for easier future modification
          and extension.

          10 test images are provided.

---------------------------------------------------------------------
> To compile in Linux:
      make all      
---------------------------------------------------------------------
> To run (this will run all programs one after the other):
      make runall 

---------------------------------------------------------------------
> Programs can be run separately:
      make run2
      make run3
      make run4
      make run6
  
> Or you can view Makefile to see the arguments that program take as
  well as threshold values.
---------------------------------------------------------------------      
To clear the object files:
      make clean
                  # This will clean object and "run-files", as well as 
                  # "output" images 
---------------------------------------------------------------------
      
      