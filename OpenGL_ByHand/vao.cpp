#include"VAO.h"

//
// return: Vertex Array Object handler
// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID); //vertex size is one... &ID is initialized in the header file.
}

// Binds the VAO and tells OpenGL this is the VAO that we want to work on. 
void VAO::Bind()
{
	glBindVertexArray(ID);
}


/*This is where we tell OpenGl where different types of data exist within our Vertex Attribute
	 Parameter 2 is the "layout" 
	 Parameter 3 is the "size", which is simply the number of components in this attribute
	 Parameter 4 is the "stride", which is the byte offset between attributes. attrib count to Bytes is translated in the function.
	 Parameter 5 is the "offset", which is where in the Vertex the specific attribute begins.
	*/
void VAO::LinkVBO(VBO& VBO, GLuint layout, int size, int stride, int offset)
{	
	VBO.Bind();

	glVertexAttribPointer(	
		layout,								// index ID of the Attribute we're specifying
		size,								// number of components in this attribute
		GL_FLOAT,							// Specify attribute component types
		GL_FALSE,							// Specifies if the data should be "Normalized"
		sizeof(float) * stride,				// Byte offset between consecutive matching attributes within the array
		(void*)( offset * sizeof(float))	// Offset specifies where the attribute begins in the array. 
	);


	glEnableVertexAttribArray(layout);
	VBO.Unbind();
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