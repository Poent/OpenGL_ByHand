#pragma once
#include "Renderer.h"

void Renderer::Draw(GLOBJECT& GLO, Shader& shader) const
{
	
		
	GLO.Bind();

#ifdef DEBUG
	std::cout << OBJECT1.GetAttributeCount() << std::endl;
	std::cout << OBJECT1.GetElementCount() << std::endl;
#endif

	glDrawElements(GL_TRIANGLES, GLO.GetElementCount(), GL_UNSIGNED_INT, 0);
	GLO.Unbind();

}

void Renderer::clear(float red, float green, float blue, float alpha) const
{
	glClearColor(red, green, blue, alpha);		// set the background color
	glClear(GL_COLOR_BUFFER_BIT);
}
