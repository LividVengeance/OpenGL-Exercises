#include "CActorEnemy.h"

CActorEnemy::CActorEnemy(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture)
	: CObject(_program, _VAO, _indiceCount, _gameCamera, _texture)
{

}

void CActorEnemy::MoveActor(GLfloat deltaTime)
{

}