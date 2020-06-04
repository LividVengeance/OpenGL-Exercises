#include "CActor.h"

CActor::CActor(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture)
	: CObject(_program, _VAO, _indiceCount, _gameCamera, _texture)
{

}

void CActor::MoveInput(GLfloat deltaTime, CInput* gameInput)
{
	int playerLimitHorzontal = (Utils::SCR_WIDTH / 2) - 25;
	int playerLimitVertical = (Utils::SCR_HEIGHT / 2) - 25;

	// Move Right
	if (gameInput->getKeyState('D') == true || gameInput->getKeyState('d') == true)
	{
		if (!(objPosition.x > playerLimitHorzontal)) // 25 is half player mesh size
		{
			objPosition.x += 200.0f * deltaTime;
		}
	}
	// Move Left
	if (gameInput->getKeyState('A') == true || gameInput->getKeyState('a') == true)
	{

		if (!(objPosition.x < -playerLimitHorzontal))
		{
			objPosition.x -= 200.0f * deltaTime;
		}
	}
	// Move Up
	if (gameInput->getKeyState('W') == true || gameInput->getKeyState('w') == true)
	{
		if (!(objPosition.y > playerLimitVertical))
		{
			objPosition.y += 200.0f * deltaTime;
		}
	}
	// Move Up
	if (gameInput->getKeyState('S') == true || gameInput->getKeyState('s') == true)
	{
		if (!(objPosition.y < -playerLimitVertical))
		{
			objPosition.y -= 200.0f * deltaTime;
		}
	}
}