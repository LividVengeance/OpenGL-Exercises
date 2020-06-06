#include "CPlayScene.h"

CPlayScene::CPlayScene(CCamera* _gameCamera, CInput* _gameInput)
{
	gameCamera = _gameCamera;
	gameInput = _gameInput;

	skyboxProgram = CShaderLoader::CreateProgram("Resources/Shaders/skybox.vs",
		"Resources/Shaders/skybox.fs");

	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic-Normal.vs",
		"Resources/Shaders/Blinn-Phong.fs");

	// Gen Textures For Actor
	const char* fileLocationPlay = "Resources/Textures/BackgroundSprite.png";
	TextureGen(fileLocationPlay, &actorTex);

	gameSkybox = new CSkybox(&skyboxProgram, gameCamera);

	actorEnemyPyramid = new CPyramid();
	model = new Model("Resources/Models/Tank/Tank.obj", gameCamera);
	actorEnemy = new CActorEnemy(&program, actorEnemyPyramid->GetVAO(), actorEnemyPyramid->GetIndiceCount(), gameCamera, &actorTex);

	actorSphere = new CSphere();
	gameActor = new CActor(&program, actorSphere->GetVAO(), actorSphere->GetIndiceCount(), gameCamera, &actorTex);

	gameActor->objPosition.x += 2000;
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Render()
{
	glUseProgram(program);

	view = gameCamera->CameraView();

	gameSkybox->Render();

	// Actors
	gameActor->Render();
	//actorEnemy->Render();
	model->Render(actorEnemy);

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);
}

void CPlayScene::Update(GLfloat* deltaTime, ESceneManager* _currentScene)
{
	currentScene = _currentScene;
	gameCamera->Update(*deltaTime);
	gameSkybox->Update();

	// Actors
	gameActor->Update();
	gameActor->MoveInput(*deltaTime, gameInput);
	actorEnemy->MoveActor(*deltaTime);
}

void CPlayScene::TextureGen(const char* textureLocation, GLuint* texture)
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