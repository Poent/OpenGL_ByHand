#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <gl\glew.h>
#include <vbo.h>

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO& VBO, GLuint layout, int size, int stride, int offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();

	GLuint * GetID();
};
#endif