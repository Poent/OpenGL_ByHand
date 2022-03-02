#ifndef VBO_CLASS_H
#define VBO_CLASS_H 

#include <gl\glew.h>
#include <glerror.h>

class VBO
{
public:
	// An interger for storing the ID of the VBO
	// This get generated in the VBO constructor. 
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO();


	void Bind();
	void Unbind();
	void Update(GLfloat* vertices, GLsizeiptr size);
	void Delete();
	GLuint* GetID();
};



#endif

