#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Utilities.h"


using namespace glm;

class CCamera
{
public:
	CCamera(GLint* program);
	~CCamera();

	void Update(GLfloat deltaTime);
	mat4 CameraView();

private:

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = Utils::SCR_WIDTH;
	const unsigned int SCR_HEIGHT = Utils::SCR_HEIGHT;

	// Camera Variables
	vec3 camPos = vec3(0.0f, 0.0f, 3.0f);
	vec3 camLookDir = vec3(0.0f, 0.0f, -1.0f);
	vec3 camUpDir = vec3(0.0f, 1.0f, 0.0f);

	float timeElapsed = 0;

	GLint* program;

	glm::mat4 view;
};