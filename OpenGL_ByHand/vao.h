#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <gl\glew.h>
#include <vbo.h>

class VAO
{
	public:
		// ID reference for the Vertex Array Object (This is just an interger)
		GLuint ID;
		
		// Constructor that generates a VAO ID - see cpp file for details
		VAO();

		/*
		 Tell OpenGl where different types of data exist within our Vertex Attribute
			Parameter 1 is the VBO, used to bind the VBO and update the attributes within that buffer
			Parameter 2 is the "layout" (index ID of the Attribute we're specifying)
			Parameter 3 is the "size", which is simply the number of components in this attribute
			Parameter 4 is the "stride", which is the byte offset between attributes. attrib count to Bytes is translated in the function.
			Parameter 5 is the "offset", which is where in the Vertex the specific attribute begins.
		*/
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