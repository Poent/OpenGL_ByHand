#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <gl\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);


class Shader
{
	public:
		unsigned int shader;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();

};

std::string get_file_contents(const char* filename);

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

static unsigned int CompileShader(unsigned int type, const std::string& source);

#endif