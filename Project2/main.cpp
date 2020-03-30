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
#include "CObject.h"
#include "ShaderLoader.h"


int main(int argc, char** argv)
{
	CGameManager mainGameManager(argc, argv);
	mainGameManager.ManagerMain();

	return(0);
}