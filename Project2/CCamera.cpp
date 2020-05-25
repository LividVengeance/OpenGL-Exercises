#pragma

#include "CCamera.h"

CCamera::CCamera(GLint* _program)
{
	program = _program;
	// Orthographic Center Camera
	mat4 proj;

	/// Ortho Cam with origin (0,0) in the top left
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	//proj = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);
	GLuint projLoc = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

CCamera::~CCamera()
{
}

mat4 CCamera::CameraView()
{
	float halfScreenWidth = (float)SCR_WIDTH * 0.5f;
	float halfScreenHeight = (float)SCR_HEIGHT * 0.5f;
	mat4 proj;
	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);

	GLuint projLoc = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));

	GLuint viewLoc = glGetUniformLocation(*program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	return(view);
}

void CCamera::Update(GLfloat deltaTime)
{
	timeElapsed += deltaTime;
	GLfloat radius = 5.0f;
	camPos.x = sin(timeElapsed) * radius;
	camPos.y = 1.5f;
	camPos.z = cos(timeElapsed) * radius;

	//view = lookAt(camPos, camPos + camLookDir, camUpDir);
	view = glm::lookAt(camPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		camUpDir);
}