#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CAudio.h"
#include "CCamera.h"
#include "CInput.h"
#include "CMesh.h"
#include "CPyramid.h"
#include "CTextLabel.h"
#include "CShaderLoader.h"


class CGameManager
{
public:
	CGameManager(int argc, char** argv);
	~CGameManager();

	void CreateAudioSystem();

	void KeyBoardDown(unsigned char key, int x, int y);
	void KeyBoardUp(unsigned char key, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void Update();
	void Render();
	void ManagerMain();

private:
	GLuint VBO, EBO, VAO;
	FMOD::System* audioSystem;

	CCamera* gameCamera;

	CInput* GameInputs;

	CTextLabel* labelExample;

	CPyramid* gamePyramid;

	GLfloat currentTime, previousTime, deltaTime;
	GLint program;
};