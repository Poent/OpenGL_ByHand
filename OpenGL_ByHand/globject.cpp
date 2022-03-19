#include <globject.h>
#include <glerror.h>

//#define DEBUG


GLOBJECT::GLOBJECT(GLfloat* vertices, GLsizeiptr vert_size, GLuint* elementIndices, GLsizeiptr eind_size, GLenum ArrayType, GLboolean Normalized, int attributeCount, int attributeSize, int stride)
	:	v_count( vert_size / sizeof(vertices[0])),
		a_count( attributeCount), 
		e_count( eind_size / sizeof(elementIndices[0]))
{
	int a = vert_size;
	int b = sizeof(vertices[0]);
	glGenVertexArrays(1, &vao_id);				//Setup Vertex Array ID
	glBindVertexArray(vao_id);					//Bind the Vertex Array

	glGenVertexArrays(1, &vbo_id);				//Setup the Vertex Buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &ebo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eind_size, elementIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < attributeCount; i++)
	{	
#ifdef DEBUG
		std::cout << "Linking Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;
#endif
		GLCall(glVertexAttribPointer(
			i,											// index ID of the Attribute we're specifying
			attributeSize,								// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
			ArrayType,									// Specify attribute component types
			Normalized,									// Specifies if the data should be "Normalized"
			sizeof(float) * stride,						// Byte offset between consecutive attributes within the array
			(void*)(attributeSize * i * sizeof(float))		// Offset specifies where the attribute begins in the array. 
		));

		GLCall(glEnableVertexAttribArray(i));

	}

}


//Definition without Element Array index
GLOBJECT::GLOBJECT(GLfloat* vertices, GLsizeiptr vert_size, GLenum ArrayType, GLboolean Normalized, int attributeCount, int attributeSize, int stride)
	: a_count(attributeCount)
{
	glGenVertexArrays(1, &vao_id);				//Setup Vertex Array ID
	glBindVertexArray(vao_id);					//Bind the Vertex Array

	glGenVertexArrays(1, &vbo_id);				//Setup the Vertex Buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &ebo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, eind_size, elementIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < attributeCount; i++)
	{
	
#ifdef DEBUG
		std::cout << "Updating Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;
#endif

		GLCall(glVertexAttribPointer(
			i,											// index ID of the Attribute we're specifying
			attributeSize,								// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
			GL_FLOAT,									// Specify attribute component types
			GL_FALSE,									// Specifies if the data should be "Normalized"
			sizeof(float) * stride,						// Byte offset between consecutive matching attributes within the array
			(void*)(stride * i * sizeof(float) / 2)			// Offset specifies where the attribute begins in the array. 
		));

		GLCall(glEnableVertexAttribArray(i));

	}
}

GLOBJECT::GLOBJECT(GLfloat* vertices, GLsizeiptr vert_size, GLuint* elementIndices, GLsizeiptr eind_size, GLenum ArrayType, GLboolean Normalized, int attributeCount, int attributeSize, int stride, bool texture)
	:	v_count(vert_size / sizeof(vertices[0])),
		a_count(attributeCount),
		e_count(eind_size / sizeof(elementIndices[0])) 
{


	glGenVertexArrays(1, &vao_id);				//Setup Vertex Array ID
	glBindVertexArray(vao_id);					//Bind the Vertex Array

	glGenVertexArrays(1, &vbo_id);				//Setup the Vertex Buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &ebo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eind_size, elementIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < 2; i++)
	{
		GLCall(glVertexAttribPointer(
			i,												// index ID of the Attribute we're specifying
			attributeSize,									// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
			ArrayType,										// Specify attribute component types
			Normalized,										// Specifies if the data should be "Normalized"
			sizeof(float) * stride,							// Byte offset between consecutive attributes within the array
			(void*)(attributeSize * i * sizeof(float))		// Offset specifies where the attribute begins in the array. 
		));

		GLCall(glEnableVertexAttribArray(i));

	}

	GLCall(glVertexAttribPointer(
		2,												// index ID of the Attribute we're specifying
		2,												// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
		ArrayType,										// Specify attribute component types
		Normalized,										// Specifies if the data should be "Normalized"
		sizeof(float) * stride,							// Byte offset between consecutive attributes within the array
		(void*)(attributeSize * 2 * sizeof(float))		// Offset specifies where the attribute begins in the array. 
	));

	GLCall(glEnableVertexAttribArray(2));


	


}



void GLOBJECT::Update(GLfloat* vertices, GLsizeiptr vert_size, int attributeCount, int attributeSize, int stride)
{

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < attributeCount; i++)
	{
#ifdef DEBUG
		std::cout << "GLOBJECT::UPDATE..." << std::endl;
		std::cout << "Linking Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;
#endif
		GLCall(glVertexAttribPointer(
			i,											// index ID of the Attribute we're specifying
			attributeSize,								// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
			GL_FLOAT,									// Specify attribute component types
			GL_FALSE,									// Specifies if the data should be "Normalized"
			sizeof(float) * stride,						// Byte offset between consecutive matching attributes within the array
			(void*)(stride * i * sizeof(float) / 2)			// Offset specifies where the attribute begins in the array. 
		));
	}
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

}

void GLOBJECT::Bind() const
{
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);

}

void GLOBJECT::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}



void GLOBJECT::PrintID() {
	std::cout << "VAO1.GetID(): " << vao_id << std::endl;
	std::cout << "VBO1.GetID(): " << vbo_id << std::endl;
	std::cout << "EBO1.GetID(): " << ebo_id << std::endl;
}

void GLOBJECT::Delete() 
{
	glDeleteVertexArrays(1, &vao_id);
	glDeleteVertexArrays(1, &vbo_id);
	glDeleteVertexArrays(1, &ebo_id);

}


