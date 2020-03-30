#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"
#include "CGameManager.h"
#include "ShaderLoader.h"

using namespace glm;

class CObject
{
public:
	CObject();
	~CObject();

	mat4 Translation(vec3 objPosition);
	mat4 Rotation(vec3 rotationAxis, float angle);
	mat4 Scale(vec3 objScale, float scaleAmount);
	mat4 Combine(mat4 translationMatrix, mat4 rotationMatrix, mat4 scaleMatrix);

private:

};