#ifndef GLBOJECT_H
#define GLOBJECT_H

#include <iostream>

#include <vao.h>
#include <vbo.h>
#include <ebo.h>

class GLOBJECT {
	public:
		//Default constructor
		//We will use this to load up all the information about our Mesh
		GLOBJECT(
			GLfloat* vertices,  //Import the Array of vertices
			GLuint* indices,    //This is our EBO index for the verts
			int attributeCount, //This is the number of attributes per vertex
			//FIX ME (size may not always be the same per vertex attribute)
			int size,			//This is the size of the attributes (probably need a better way to process this)
			int stride);

		VAO VAO1;
		VBO VBO1;
		EBO EBO1;

		void Bind();
		void Unbind();
		void Update(GLfloat * vertices, GLuint * indices);
		void GetID();
		void Delete();


};


#endif