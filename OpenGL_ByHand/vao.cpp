#include"VAO.h"

//
// \return: Vertex Array Object handler
// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout, int size, int stride, int offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)( offset * sizeof(float)));
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}

GLuint * VAO::GetID()
{
	return &ID;
}