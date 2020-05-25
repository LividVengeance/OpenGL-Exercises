#include "CActor.h"

CActor::CActor(CInput* gameInputs, CCamera* camera, GLint program)
{
	actorInputs = gameInputs;

	float xSize = 30;
	float ySize = 30;

	const char* fileLocation = "Resources/Textures/PlayerSprite.png";
	actorMesh = new CMesh(program, camera, xSize, ySize, fileLocation);
}

CActor::~CActor()
{
}

void CActor::Update()
{
	actorMesh->Update();
}

void CActor::Render()
{
	actorMesh->Render();
}

void CActor::MoveInput(GLfloat deltaTime)
{
	int playerLimitHorzontal = (Utils::SCR_WIDTH / 2) - 25;
	int playerLimitVertical = (Utils::SCR_HEIGHT / 2) - 25;
#pragma region ToDelete

	// Move Right
	if (actorInputs->getKeyState('D') == true || actorInputs->getKeyState('d') == true)
	{
		if (!(actorMesh->objPosition.x > playerLimitHorzontal)) // 25 is half player mesh size
		{
			actorMesh->objPosition.x += 200.0f * deltaTime;
		}
	}
	// Move Left
	if (actorInputs->getKeyState('A') == true || actorInputs->getKeyState('a') == true)
	{

		if (!(actorMesh->objPosition.x < -playerLimitHorzontal))
		{
			actorMesh->objPosition.x -= 200.0f * deltaTime;
		}
	}
	// Move Up
	if (actorInputs->getKeyState('W') == true || actorInputs->getKeyState('w') == true)
	{
		if (!(actorMesh->objPosition.y > playerLimitVertical))
		{
			actorMesh->objPosition.y += 200.0f * deltaTime;
		}
	}
	// Move Up
	if (actorInputs->getKeyState('S') == true || actorInputs->getKeyState('s') == true)
	{
		if (!(actorMesh->objPosition.y < -playerLimitVertical))
		{
			actorMesh->objPosition.y -= 200.0f * deltaTime;
		}
	}
#pragma endregion

	//if(actorInputs->)
}
