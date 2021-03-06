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

float rect[] = {
 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	2.0f, 2.0f,		// Top-left
 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	2.0f, 0.0f,		// Top-right
-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		// Bottom-right
-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 2.0f		// Bottom-left
};


GLuint elements[] = {
		0, 1, 3,
		1, 2, 3
};


float circArray[] = {
 0.0f,		0.5f,
 0.203f,	0.457f,
 0.372f,	0.335f,
 0.476f,	0.155f,
 0.497f,	-0.0523f,
 0.433f,	-0.25f,
 0.294f,	-0.405f,
 0.104f,	-0.489f,
-0.104f,	-0.489f,
-0.294f,	-0.405f,
-0.433f,	-0.25f,
-0.497f,	-0.0523f,
-0.476f,	0.155f,
-0.372f,	0.335f,
-0.203f,	0.457f
};

GLuint circElements[15];