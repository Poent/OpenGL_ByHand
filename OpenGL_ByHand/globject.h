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
			GLuint* elementIndices,	// pointer to the element array mapping
			GLsizeiptr eind_size,		// size of the element array
			int numAttributes,			// number of attrubtes in the vertex array
			int stride					// distance between attribute values
		);

		void updateBuffer(
			GLfloat* vertices,			// pointer to the verex array
			GLsizeiptr vert_size,		// size of the indices array
			GLuint* elementIndices,	// pointer to the element array mapping
			GLsizeiptr eind_size,		// size of the element array
			int numAttributes,			// number of attrubtes in the vertex array
			int stride					// distance between attribute values
		);



		void Bind();
		void Unbind();
		void Update(GLfloat * vertices, GLuint * indices);
		void GetID();
		void Delete();

private:
	GLuint vao_id, vbo_id, ebo_id;


};


#endif