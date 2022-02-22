#include <math.h>

float Triforce[] = 
{//|			postions 		           |   |      Color   	   |
  -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        1.0f, 0.0f, 0.0f,			  //Lower Left
   0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        0.0f, 1.0f, 0.0f,			  //upper corner
   0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    0.0f, 0.0f, 1.0f,		  	  //Lower Right

  -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	  1.0f, 0.0f, 0.0f,		      //Inner Left
   0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	  0.0f, 1.0f, 0.0f,		      //Inner right
   0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		  0.0f, 0.0f, 1.0f,			  //Inner Down
};

unsigned int TriforceIndicies[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};


float brick[] = {
	-0.05f, 0.05f, 0.0f, 
	-0.05f, -0.05f, 0.0f,
	0.05f, -0.05f, 0.0f, 
	0.05f, 0.05f, 0.0
};

unsigned int brickEDO[] = {
	0, 1, 2,
	2, 3, 0
};

float BrickTex[] = {
	-0.05f, -0.05f, //bottom left
	0.05f, -0.05f,  //bottom right
	0.05f, 0.05f,
};


float line[] = {
	0.0f, 1.0f,
	0.0f, 0.0f
};

float newLine[];


/* Vertex array to hold terrain layout
- To match our parameters we need 7 points equalliy split across the game world.
- Each point starts out initialized to zero
*/
float terrain[] = {
	0.0f, 0.0f, //1
	0.0f, 0.0f, //2
	0.0f, 0.0f, //3
	0.0f, 0.0f, //4
	0.0f, 0.0f, //5
	0.0f, 0.0f, //6
	0.0f, 0.0f, //7
};