#pragma

#include "CCamera.h"

CCamera::CCamera()
{
	// 3D Camera
	camPos = vec3(0.0f, 0.0f, 3.0f);
	camLookDir = vec3(0.0f, 0.0f, -1.0f);
	camUpDir = vec3(0.0f, 1.0f, 0.0f);

	// 2D Camera
	camPos2D = vec3(0.0f, 0.0f, 3.0f);
	camLookDir2D = vec3(0.0f, 0.0f, -1.0f);
	camUpDir2D = vec3(0.0f, 1.0f, 0.0f);
}

CCamera::~CCamera()
{
}

mat4 CCamera::CameraView()
{
	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);
	return(view);
}

mat4 CCamera::CameraView2D()
{
	proj2D = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	return(glm::lookAt(camPos2D, camPos2D + camLookDir2D, camUpDir2D));
}

void CCamera::Update(GLfloat deltaTime)
{
	timeElapsed += deltaTime;
	GLfloat radius = 5.0f;
	camPos.x = sin(timeElapsed) * radius;
	camPos.y = 1.5f;
	camPos.z = cos(timeElapsed) * radius;

	view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), camUpDir);

	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);
}

void CCamera::Update2D()
{
	view = glm::lookAt(camPos2D, camPos2D + camLookDir2D, camUpDir2D);
	proj2D = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
}

mat4 CCamera::CameraProjection()
{
	return(proj);
}

mat4 CCamera::CameraProjection2D()
{
	return(proj2D);
}

vec3 CCamera::GetCamPos()
{
	return(camPos);
}