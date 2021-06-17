#include"VBO.h"
#include <iostream>

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

#ifdef DEBUG
	std::cout << "VBO Define verts: " << vertices << std::endl;
	std::cout << "VBO Define size: " << size << std::endl;
#endif
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Update(GLfloat* vertices, GLsizeiptr size)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

#ifdef DEBUG
	std::cout << "Update verts: " << vertices << std::endl;
	std::cout << "VBO Define size: " << size << std::endl;
#endif
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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