#pragma once

// Dependency Includes
#include <glew.h>
#include <freeglut.h>

// Library Includes
#include <iostream>

class ShaderLoader
{
	
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);

private:
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char *filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
