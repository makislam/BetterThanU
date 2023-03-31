# BetterThanU

This project was created using a lego EV3 robot and the solve instructions file is to be compiled in RobotC. The analysis.cpp file is a C++ program. 

To run the analysis program, simply compile, build, and run the file and it will prompt you to input the cube state. 
The cube state should be in the form of moves used to scramble the cube. An example of this is like "DRDBRUD'BFFLBBUURUUFFRLBBLF'D" from the scramble 
D R2 B R U D' B F2 L B2 U2 R U2 F2 R L B2 L F' D. The prime " ' " indicates a counter clockwise turn and a 2 means that the previous move is completed twice. 

The program will then create a text file called "moves.txt" storing the solution moves. 

F: = Green side clockwise turn
F’ = A = Green side counterclockwise turn

U: Yellow side clockwise turn
U’ = C = yellow side counterclockwise turn

D: = White side clockwise turn
D’: = E = white side counterclockwise turn

R: = Orange side clockwise turn
R’: = G = orange side counterclockwise turn

L: = Red side clockwise turn
L’: = H = red side counterclockwise turn

B: = Blue side clockwise turn
B’: = I = blue side counterclockwise turn

When the txt file is made, import the text file to the robot through 
Robot >> LEGO Brick >> File Management Utility >> rc-data >> download.

Place cube into the robot and ensure that the orientation when mixed is consistent with orientation when placed into the robot.
