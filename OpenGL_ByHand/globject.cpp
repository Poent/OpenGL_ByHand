#include <globject.h>
#include <glerror.h>


GLOBJECT::GLOBJECT(GLfloat* vertices, GLsizeiptr vert_size, GLuint* elementIndices, GLsizeiptr eind_size,int attributeCount, int attributeSize, int stride)
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
	for (int i = 0; i < attributeCount; i++)
	{	
		std::cout << "Linking Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;

		GLCall(glVertexAttribPointer(
			i,											// index ID of the Attribute we're specifying
			attributeSize,								// Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4
			GL_FLOAT,									// Specify attribute component types
			GL_FALSE,									// Specifies if the data should be "Normalized"
			sizeof(float) * stride,						// Byte offset between consecutive matching attributes within the array
			(void*)(stride * i * sizeof(float)/2)			// Offset specifies where the attribute begins in the array. 
		));

		GLCall(glEnableVertexAttribArray(i));

	}

}


//Definition without Element Array index
GLOBJECT::GLOBJECT(GLfloat* vertices, GLsizeiptr vert_size, int attributeCount, int attributeSize, int stride)
{
	glGenVertexArrays(1, &vao_id);				//Setup Vertex Array ID
	glBindVertexArray(vao_id);					//Bind the Vertex Array

	glGenVertexArrays(1, &vbo_id);				//Setup the Vertex Buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < attributeCount; i++)
	{
		std::cout << "Linking Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;

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


void GLOBJECT::Update(GLfloat* vertices, GLsizeiptr vert_size, int attributeCount, int attributeSize, int stride)
{

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	for (int i = 0; i < attributeCount; i++)
	{
		std::cout << "Linking Attribute: " << i << std::endl;
		std::cout <<
			"index: " << i << std::endl <<
			"attributeSize: " << attributeSize << std::endl <<
			"stride: " << stride << std::endl <<
			"Offset: " << static_cast<unsigned long long>(stride) * i * sizeof(float) << std::endl;

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

void GLOBJECT::Bind()
{
	glBindVertexArray(vao_id);
}

void GLOBJECT::Unbind() 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}



void GLOBJECT::GetID() {
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