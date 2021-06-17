#include <math.h>

float points[] = {
   -0.5f, -0.5f * float(sqrt(3)) / 3,  0.0f,		//Lower Left
   0.5f,  -0.5f * float(sqrt(3)) / 3,  0.0f,		//upper corner
   0.0f, 0.5f * float(sqrt(3)) * 2 / 3,  0.0f,			//Lower Right

  -0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,			//Inner Left
  0.5f / 2, 0.5f * float(sqrt(3)) / 6,  0.0f,			//Inner right
  0.0f, -0.5f * float(sqrt(3)) / 3,  0.0f			//Inner Down
};

unsigned int indicies[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

float line[] = {
	0.0f, 1.0f,
	0.0f, 0.0f
};

float newLine[];