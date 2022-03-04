#include"VBO.h"
#include <iostream>



// Constructor that generates a Vertex Buffer Object and links it to vertices
// Input an array of verticies and the size of that array. 
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// This is an openGL function to generate the buffer ID.
	glGenBuffers(1, &ID);
	// tells OpenGL the type and buffer ID we want to bind (work with)
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Tell open GL to fill the bound buffer with our vertex data.
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

#ifdef DEBUG
	std::cout << "VBO Define verts: " << vertices << std::endl;
	std::cout << "VBO Define size: " << size << std::endl;
#endif
}


//We're adding this so we can create the GLOBJECT class. 
//It allows us to construct the object first and THEN update it. 
//Leaving Bind in here... but should probably move it out for consistency
///*
VBO::VBO() {
	// This is an openGL function to generate the buffer ID.
	GLCall(glGenBuffers(1, &ID));
	// tells OpenGL the type and buffer ID we want to bind (work with)
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}
//*/

// Tells OpenGL to use this VBO (uses the internal object ID)
void VBO::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VBO::Update(GLfloat* vertices, GLsizeiptr size)
{
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));

#ifdef DEBUG
	std::cout << "Update verts: " << vertices << std::endl;
	std::cout << "VBO Define size: " << size << std::endl;
#endif
}

// Unbinds the VBO
void VBO::Unbind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

GLuint* VBO::GetID()
{
	return &ID;
}