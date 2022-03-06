#pragma once

#include <iostream>
#include <GL/glew.h>


class GLOBJECT {


	public:
		//Default constructor
		//We will use this to load up all the information about our Mesh
		GLOBJECT(
			GLfloat* vertices,			// pointer to the verex array
			GLsizeiptr vert_size,		// size of the indices array
			GLuint* elementIndices,		// pointer to the element array mapping
			GLsizeiptr eind_size,		// size of the element array
			GLenum ArrayType,			// Array Type
			GLboolean Normalized,		// Normalized or not
			int attributeCount,			// number of attrubtes in the vertex array
			int attributeSize,			// how big is each attribute set
			int stride					// distance between attribute values
		);

		//Creaet without a Element Index Array
		GLOBJECT(
			GLfloat* vertices,			// pointer to the verex array
			GLsizeiptr vert_size,		// size of the indices array
			GLenum ArrayType,			// Array Type
			GLboolean Normalized,		// Normalized or not
			int attributeCount,			// number of attrubtes in the vertex array
			int attributeSize,			// how big is each attribute set
			int stride					// distance between attribute values
		);


		void Bind() const;
		void Unbind() const;
		void Update(
			GLfloat* vertices,
			GLsizeiptr vert_size,
			int attributeCount,
			int attributeSize,
			int stride
		);
		void PrintID();

		void Delete();
		inline unsigned int GetAttributeCount()		{	return a_count;			}
		inline unsigned int GetElementCount()		{	return e_count;			}
		inline unsigned int GetElementType()		{	return a_type;			}
		inline unsigned int GetElementNormalized()	{	return normalized;	}
		inline unsigned int GetVertexCount()		{	return v_count;			}


private:
	GLuint vao_id = 0, vbo_id = 0, ebo_id = 0;
	unsigned int 
		a_count = 0,
		e_count = 0,
		v_count = 0,
		a_type = 0;
	bool normalized = 0;
	
};

