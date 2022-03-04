#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <gl\glew.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	
	EBO();
	 
	
	// Binds the EBO
	void Bind();
	// Update the VBO
	void Update(GLuint* indices, GLsizeiptr size);
	// Unbinds the EBO
	void Unbind();
	// returns the EBO ID
	GLuint* GetID();

	// Deletes the EBO
	void Delete();
};

#endif