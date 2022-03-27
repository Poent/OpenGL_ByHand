#pragma once
#include "Renderer.h"

// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


void Renderer::Draw(GLOBJECT& GLO, Shader& shader, int type) const
{
	switch(type){
	//Draw Triangles with EBO (don't require connection).
	case 0:
		GLO.Bind();
		glDrawElements(GL_TRIANGLES, GLO.GetElementCount(), GL_UNSIGNED_INT, 0);
		GLO.Unbind();
		break;
		
	//Draw a line loop with EBO (circle)
	case 1:
		GLO.Bind();
		glDrawElements(GL_LINE_LOOP, GLO.GetElementCount(), GL_UNSIGNED_INT, 0);
		GLO.Unbind();
		break;
	case 2:
		GLO.Bind();
		glDrawElements(GL_POLYGON, GLO.GetElementCount(), GL_UNSIGNED_INT, 0);
		GLO.Unbind();
	}
}

void Renderer::clear(float red, float green, float blue, float alpha) const
{
	glClearColor(red, green, blue, alpha);		// set the background color
	glClear(GL_COLOR_BUFFER_BIT);
}
