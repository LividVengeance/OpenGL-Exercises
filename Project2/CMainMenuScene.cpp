#include "CMainMenuScene.h"

CMainMenuScene::CMainMenuScene(CCamera* _gameCamera, CInput* _gameInput)
{
	gameCamera = _gameCamera;
	gameInput = _gameInput;

	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");

	// Gen Textures For Buttons
	const char* fileLocationPlay = "Resources/Textures/playSprite.png";
	TextureGen(fileLocationPlay, &playButtonTex);
	const char* fileLocationExit = "Resources/Textures/exitSprite.png";
	TextureGen(fileLocationExit, &exitButtonTex);
	const char* fileLocationTitle = "Resources/Textures/titleSprite.png";
	TextureGen(fileLocationTitle, &titleTex);
	// Create Type
	buttonPlane = new CPlane(200.0f, 50.0f);
	
	playButtonObj = new CObject(&program, buttonPlane->GetVAO(), buttonPlane->GetIndiceCount(), gameCamera, &playButtonTex);
	exitButtonObj = new CObject(&program, buttonPlane->GetVAO(), buttonPlane->GetIndiceCount(), gameCamera, &exitButtonTex);
	titleObj = new CObject(&program, buttonPlane->GetVAO(), buttonPlane->GetIndiceCount(), gameCamera, &titleTex);

	playButtonObj->objScaleAmount = 0.005f;
	playButtonObj->objPosition.x = -1.5f;
	playButtonObj->objPosition.y = 0.3f;

	exitButtonObj->objScaleAmount = 0.005f;
	exitButtonObj->objPosition.x = -1.5f;
	exitButtonObj->objPosition.y = 0.6f;

	titleObj->objScaleAmount = 0.005f;
	titleObj->objPosition.x = -1.3f;
	titleObj->objPosition.y = 0.9f;
}

CMainMenuScene::~CMainMenuScene()
{
}

void CMainMenuScene::Render()
{
	glUseProgram(program);
	glDisable(GL_CULL_FACE);

	view = gameCamera->CameraView2D();

	playButtonObj->Render();
	exitButtonObj->Render();

	titleObj->Render();

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);
}

void CMainMenuScene::Update(GLfloat* deltaTime, ESceneManager* _currentScene)
{
	currentScene = _currentScene;
	gameCamera->Update2D();

	// Objects
	playButtonObj->Update();
	exitButtonObj->Update();
	titleObj->Update();

	// Mouse has clicked button check
	if (Button(200, 50, playButtonObj) || gameInput->getKeyState('e'))
	{
		// Play Button
		*currentScene = EPlayScene;
	}
	if (Button(200, 50, exitButtonObj))
	{
		// Exit program
		//glutDestroyWindow(program);
	}
}

bool CMainMenuScene::Button(float width, float height, CObject* _buttonObj)
{
	mouseX = gameInput->getMouseX();
	mouseY = gameInput->getMouseY();

	float offSetX = Utils::SCR_WIDTH / 2;
	float offSetY = Utils::SCR_HEIGHT / 2;

	if (-(offSetX - mouseX) > _buttonObj->objPosition.x - width / 2 &&
		-(offSetX - mouseX) < _buttonObj->objPosition.x + width / 2 &&
		offSetY - mouseY > _buttonObj->objPosition.y - height / 2 &&
		offSetY - mouseY < _buttonObj->objPosition.y + height / 2 &&
		(gameInput->getClick(0) || gameInput->getClick(1)))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

void CMainMenuScene::TextureGen(const char* textureLocation, GLuint* texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	int width, height;
	unsigned char* image1 = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}