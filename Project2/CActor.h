#pragma once

#include "CMesh.h"
#include "CInput.h"

class CActor
{
public:
	CActor(CInput* gameInputs, CCamera* camera, GLint program);
	~CActor();

	void Update();
	void Render();
	void MoveInput(GLfloat deltaTime);

	vec3 actorPostion;
	vec3 actorRotation;
	vec3 actorScale;

	CMesh* actorMesh;
	glm::mat4 model;

private:
	CInput* actorInputs;
};