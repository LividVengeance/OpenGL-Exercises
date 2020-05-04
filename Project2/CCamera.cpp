#pragma

#include "CCamera.h"

CCamera::CCamera(GLint program)
{
	// Orthographic Center Camera
	mat4 proj;

	/// Ortho Cam with origin (0,0) in the top left
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);

	/// Ortho Cam with origin (0,0) in the center
	//proj - ortho(0.0f, (float)SCR_WIDTH, (float)SCR_HEIGHT, 0.0f, 0.1f, 100.0f);

	GLuint projLoc = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

CCamera::~CCamera()
{
}

mat4 CCamera::CameraView()
{
	mat4 view = lookAt(camPos, camPos + camLookDir, camUpDir);
	return(view);
}

void CCamera::Update(GLfloat deltaTime)
{
	timeElapsed += deltaTime;
	GLfloat radius = 2.0f;
	camPos.x = sin(timeElapsed) * radius;
	camPos.y = 1.5f;
	camPos.z = cos(timeElapsed) * radius;

	glm::mat4 view = glm::lookAt(camPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		camUpDir);
}