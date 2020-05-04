#pragma once
#include "CCamera.h"
#include "CMesh.h"

class CPyramid
{
public:
	CPyramid(CCamera* camera, GLint program);
	~CPyramid();

	void Render();

	CMesh* pyramidMesh;

private:

};

