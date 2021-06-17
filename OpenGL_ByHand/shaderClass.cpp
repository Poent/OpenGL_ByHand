#include <shaderClass.h>

std::string get_file_contents(const char* filename) 
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//Attached the shader source (&src) to the shader object
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//error handling (ish)

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;

}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{

	//set compiled Vertex Shader and Fragment Shader IDs to vs and fs
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//Create the shader program
	unsigned int program = glCreateProgram();
	//attach the compiled vs and fs to the shader program
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	//wrap up and link all shaders together into the shader program
	glLinkProgram(program);
	glValidateProgram(program);

	//delete the now useless shader programs (since they're loaded into the GPU).
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//std::cout << vertexCode << std::endl;
	//std::cout << fragmentCode << std::endl;
	//we conver to const char* in compileShader();
	//const char* vertexSource = vertexCode.c_str();
	//const char* fragmentSource = fragmentCode.c_str();

	shader = createShader(vertexCode, fragmentCode);

}

void Shader::Activate()	
{
	glUseProgram(shader);
}

void Shader::Delete() 
{
	glDeleteShader(shader);
}