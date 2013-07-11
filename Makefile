########################################
##
## Makefile
## LINUX compilation 
##
##############################################

#FLAGS
C++FLAG = -g  

MATH_LIBS = -lm

EXEC_DIR=.


.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

#Second Program (Edge Detection)

Cpp_OBJ2=Image.o Line.o Pgm.o edge_road_detector.o

PROGRAM_NAME2=edge_road_detector

$(PROGRAM_NAME2): $(Cpp_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Third Program (Hough Algorithm)

Cpp_OBJ3=Image.o Line.o Pgm.o line_road_detector.o

PROGRAM_NAME3=line_road_detector

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)

#Fourth Program (FloodFill Algorithm)

Cpp_OBJ4=Image.o Line.o Pgm.o floodFill.o

PROGRAM_NAME4=floodFill

$(PROGRAM_NAME4): $(Cpp_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ4) $(INCLUDES) $(LIBS_ALL)	

#Sixth Program (Remove Hough Lines)

Cpp_OBJ6=Image.o Line.o Pgm.o remove_lines.o

PROGRAM_NAME6=remove_lines

$(PROGRAM_NAME6): $(Cpp_OBJ6)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ6) $(INCLUDES) $(LIBS_ALL)	


all: 
	make $(PROGRAM_NAME2) $(PROGRAM_NAME3) $(PROGRAM_NAME4) $(PROGRAM_NAME6)

all2:
	make $(PROGRAM_NAME2)

all3:
	make $(PROGRAM_NAME3)

all4:
	make $(PROGRAM_NAME4)

all5: 
	make $(PROGRAM_NAME) 

all6:
	make $(PROGRAM_NAME6)


runall:
	make run2
	make run3
	make run4
	make run6

 
run2:
	./edge_road_detector road1.pgm edges_road1.pgm 600
	./edge_road_detector road2.pgm edges_road2.pgm 350
	./edge_road_detector road3.pgm edges_road3.pgm 600
	./edge_road_detector road4.pgm edges_road4.pgm 200
	./edge_road_detector road5.pgm edges_road5.pgm 400
	./edge_road_detector road6.pgm edges_road6.pgm 400
	./edge_road_detector road7.pgm edges_road7.pgm 300
	./edge_road_detector road8.pgm edges_road8.pgm 500
	./edge_road_detector road9.pgm edges_road9.pgm 250


run3:
	./line_road_detector edges_road1.pgm lines_road1.pgm 160
	./line_road_detector edges_road2.pgm lines_road2.pgm 100
	./line_road_detector edges_road3.pgm lines_road3.pgm 150
	./line_road_detector edges_road4.pgm lines_road4.pgm 250
	./line_road_detector edges_road5.pgm lines_road5.pgm 160
	./line_road_detector edges_road6.pgm lines_road6.pgm 150
	./line_road_detector edges_road7.pgm lines_road7.pgm 150
	./line_road_detector edges_road8.pgm lines_road8.pgm 145
	./line_road_detector edges_road9.pgm lines_road9.pgm 115

run4:
	./floodFill lines_road1.pgm detected_road1.pgm
	./floodFill lines_road2.pgm detected_road2.pgm
	./floodFill lines_road3.pgm detected_road3.pgm
	./floodFill lines_road4.pgm detected_road4.pgm
	./floodFill lines_road5.pgm detected_road5.pgm
	./floodFill lines_road6.pgm detected_road6.pgm
	./floodFill lines_road7.pgm detected_road7.pgm
	./floodFill lines_road8.pgm detected_road8.pgm
	./floodFill lines_road9.pgm detected_road9.pgm

run6:
	./remove_lines detected_road1.pgm final_road1.pgm
	./remove_lines detected_road2.pgm final_road2.pgm
	./remove_lines detected_road3.pgm final_road3.pgm
	./remove_lines detected_road4.pgm final_road4.pgm
	./remove_lines detected_road5.pgm final_road5.pgm
	./remove_lines detected_road6.pgm final_road6.pgm
	./remove_lines detected_road7.pgm final_road7.pgm
	./remove_lines detected_road8.pgm final_road8.pgm
	./remove_lines detected_road9.pgm final_road9.pgm


clean:
	(rm -f *.o *.*~  edge_road_detector line_road_detector ;)
	(rm -f detected_road*.pgm edges_road*.pgm lines_road*.pgm floodFill ;)
	(rm -f remove_lines final_road*.pgm;) 

(:
