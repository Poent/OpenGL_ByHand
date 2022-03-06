#ifndef GLBOJECT_H
#define GLOBJECT_H

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
			int attributeCount,			// number of attrubtes in the vertex array
			int attributeSize,			// how big is each attribute set
			int stride					// distance between attribute values
		);

		//Creaet without a Element Index Array
		GLOBJECT(
			GLfloat* vertices,			// pointer to the verex array
			GLsizeiptr vert_size,		// size of the indices array
			int attributeCount,			// number of attrubtes in the vertex array
			int attributeSize,			// how big is each attribute set
			int stride					// distance between attribute values
		);


		void Bind();
		void Unbind();
		void Update(
			GLfloat* vertices,
			GLsizeiptr vert_size,
			int attributeCount,
			int attributeSize,
			int stride
		);
		void GetID();
		void Delete();

private:
	GLuint vao_id, vbo_id, ebo_id;


};


#endif