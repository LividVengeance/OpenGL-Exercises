#include "CPyramid.h"

CPyramid::CPyramid(CCamera* camera, GLint program)
{
	pyramidPostion = vec3(0.0f, 0.0f, 0.0f);
	pyramidRotation = vec3(0.0f, 0.0f, 0.0f);
	pyramidScale = vec3(0.0f, 0.0f, 0.0f);

	float xSize = 30;
	float ySize = 30;

	const char* fileLocation = "Resources/Textures/BackgroundSprite.png";
	pyramidMesh = new CMesh(program, camera, xSize, ySize, fileLocation);
}

CPyramid::~CPyramid()
{
}

void CPyramid::Render()
{
	pyramidMesh->Render();
}

void CPyramid::Update()
{
	pyramidMesh->Update();
}