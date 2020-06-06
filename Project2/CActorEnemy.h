#pragma once
#include "CObject.h"

class CActorEnemy : public CObject
{
public:
	CActorEnemy(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture);
	void MoveActor(GLfloat deltaTime);
};