#include "CPyramid.h"

CPyramid::CPyramid(CCamera* camera, GLint program)
{
	float xSize = 50;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/PlayerSprite.png";
	pyramidMesh = new CMesh(program, camera, xSize, ySize, fileLocation);
}

CPyramid::~CPyramid()
{
}

void CPyramid::Render()
{
	pyramidMesh->Render();
}