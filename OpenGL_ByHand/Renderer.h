#pragma once

#include <iostream>
#include <GL/glew.h>
#include <globject.h>
#include <shaderClass.h>

class Renderer
{
public:
	void Draw( GLOBJECT& GLO,  Shader& shader) const;
	void clear(float red, float green, float blue, float alpha) const;

private:


};

