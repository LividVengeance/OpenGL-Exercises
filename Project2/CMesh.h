#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"

class CMesh
{
public:
	CMesh(GLint program, CCamera* camera, float xSize, float ySize, const char* textureLocation);
	~CMesh();
	void Render();
	void Render(glm::mat4 _modelMatrix);
	void Update();

	glm::vec3 objPosition;
	glm::vec3 rotationAxis;
	glm::vec3 objScale;
	float scaleAmount;
	float angle;

	GLint programMesh;
	glm::mat4 modelMatrix;

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	GLuint texture;
};

