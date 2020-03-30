#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CGameManager.h"
#include "CObject.h"
#include "ShaderLoader.h"

using namespace glm;

class CCamera
{
public:
	CCamera(GLint program);
	~CCamera();

	mat4 CameraView();

private:

	// Screen/Viewport size
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 800;

	// Camera Variables
	vec3 camPos = vec3(0.0f, 0.0f, 3.0f);
	vec3 camLookDir = vec3(0.0f, 0.0f, -1.0f);
	vec3 camUpDir = vec3(0.0f, 1.0f, 0.0f);
};