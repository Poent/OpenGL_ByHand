#include <globject.h>


GLOBJECT::GLOBJECT(	GLfloat* vertices, GLuint* indices, int attributeCount,	int size, int stride)
{
	std::cout << "VAO1 ID: " << VAO1.GetID() << std::endl;
	VAO1.Bind();

	GetActiveVBO();

	VBO VBO1(vertices, sizeof(vertices));
	

	for (int i = 0; i < attributeCount; i++)
	{
		std::cout
			<< "i: " << i
			<< " Size: " << size
			<< " Stride: " << stride
			<< " i * size: " << (i * size) 
			<< std::endl;

 		VAO1.LinkVBO(VBO1, i, size, stride, i * size);
	}

	EBO EBO1(indices, sizeof(indices));

}

void GLOBJECT::Bind() 
{
	GLCall(VAO1.Bind());
	GLCall(VBO1.Bind());
	//EBO1.Bind();
}

void GLOBJECT::Unbind() 
{
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

void GLOBJECT::Update(GLfloat * vertices, GLuint * indices) 
{
	VBO1.Update(vertices, sizeof(vertices));
	EBO1.Update(indices, sizeof(indices));
}

void GLOBJECT::GetID() {
	std::cout << "VAO1.GetID(): " << VAO1.GetID() << std::endl;
	std::cout << "VBO1.GetID(): " << VBO1.GetID() << std::endl;
	std::cout << "EBO1.GetID(): " << EBO1.GetID() << std::endl;
}

void GLOBJECT::Delete() 
{
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

}