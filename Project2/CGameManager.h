#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"
#include "CObject.h"
#include "ShaderLoader.h"



using namespace glm;
using namespace std;

class CGameManager
{
public:
	CGameManager(int argc, char** argv);
	~CGameManager();

	void Update();
	void Render();
	void ManagerMain();
	GLint GenerateTextures();

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	GLuint texture;
	GLuint texture1;

	GLfloat currentTime;
	GLint program;
};