#pragma once
#include "CCamera.h"
#include "CMesh.h"

class CPyramid
{
public:
	CPyramid(CCamera* camera, GLint program);
	~CPyramid();

	void Render();
	void Update();

	vec3 pyramidPostion;
	vec3 pyramidRotation;
	vec3 pyramidScale;

	CMesh* pyramidMesh;

private:

};

