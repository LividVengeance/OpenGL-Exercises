#pragma once

#include "CShaderLoader.h"
#include "CCamera.h"
#include "CInput.h"

#include "CActor.h"
#include "CPyramid.h"
#include "CSphere.h"

class CPlayScene
{
public:
	CPlayScene(CCamera* _gameCamera, CInput* _gameInput);
	~CPlayScene();

	void Render();
	void Update(GLfloat* deltaTime, ESceneManager* _currentScene);

	void TextureGen(const char* textureLocation, GLuint* texture);

	ESceneManager* currentScene;

	// Actor
	GLuint actorTex;
	CPyramid* actorPyramid;
	CSphere* actorSphere;
	CActor* gameActor;

	GLint program;
	CCamera* gameCamera;
	CInput* gameInput;

	mat4 view;
};

