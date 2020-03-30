#pragma once

#include "CGameManager.h"

CGameManager* globalPointerGM;

enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_UP_FIRST,
	INPUT_DOWN_FIRST,
};

InputState KeyState[255];
InputState MouseState[3];

void RenderRedirect()
{
	/// Allows glut to look at func in class
	globalPointerGM->Render();
}

void UpdateRedirect()
{
	/// Allows glut to look at func in class
	globalPointerGM->Update();
}

CGameManager::CGameManager(int argc, char** argv)
{
	globalPointerGM = this;

	GLfloat vertices[]{
		// Position				// Color			// Texture Coords
		 0.33f,  1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.33f,  1.0f,	// Top left
		 0.66f,  1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.66f,  1.0f,	// Mid left
		 1.0f,   0.5f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   0.5f,	// Bot left
		 0.66f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.66f,  0.0f,	// Top Right
		 0.33f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.33f,  0.0f,	// Mid Right
		 0.0f,   0.5f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   0.5f,	// Bot Right
	};
	GLuint indices[] = {
		4, 1, 0,	// First Triangle
		4, 3, 1,	// Second Triangle
		3, 2, 1,	// Third Triangle
		5, 4, 0, 	// Fourth Triangle
	};

	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Window Title");

	// Sets up all GL function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew fails to setup will throw error message
		std::cout << "Glew Faild to initialize. Now aborting." << std::endl;
		system("pause");
	}

	// Sets the clear colour
	glClearColor(1.0, 0.0, 0.0, 1.0); // Sets to Red

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	program = ShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos + color)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glm::vec3 objPostion = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPostion);

	GLuint translateLoc = glGetUniformLocation(program, "translation");
	glUniformMatrix4fv(translateLoc, 1, GL_FALSE, glm::value_ptr(translationMatrix));

}

CGameManager::~CGameManager()
{
}

void CGameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "tex1"), 1);

	glBindVertexArray(VAO);		// Bind VAO

	//		Ceate First Hex		//
	CObject objOne;
	// Translation Matrix
	vec3 objPosition = vec3(250.0f, 250.0f, 0.0f);
	mat4 translationMatrix = objOne.Translation(objPosition);
	// Rotation Matrix
	vec3 rotationAxis = vec3(0.0f, 0.0f, 1.0f);
	float angle = 180.0f;
	mat4 rotationMatrix = objOne.Rotation(rotationAxis, angle);
	// Scale Matrix
	float scaleAmount = 1000.0f;
	vec3 objScale = vec3(0.5f, 0.5f, 0.5f);
	mat4 scaleMatrix = objOne.Scale(objScale, scaleAmount);
	// Create model matrix to combine them
	mat4 model = objOne.Combine(translationMatrix, rotationMatrix, scaleMatrix);

	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);			// Draw First Hex

	//		Ceate Second Hex		//
	CObject objTwo;
	// Translation Matrix
	vec3 objPosition1 = vec3(350.0f, 150.0f, 0.0f);
	mat4 translationMatrix1 = objTwo.Translation(objPosition1);
	// Rotation Matrix
	vec3 rotationAxis1 = vec3(0.0f, 0.0f, 1.0f);
	float angle1 = 90.0f;
	mat4 rotationMatrix1 = objTwo.Rotation(rotationAxis1, angle1);
	// Scale Matrix
	float scaleAmount1 = 500.0f;
	vec3 objScale1 = vec3(0.5f, 0.5f, 0.5f);
	mat4 scaleMatrix1 = objTwo.Scale(objScale1, scaleAmount1);
	// Create model matrix to combine them
	mat4 model1 = objTwo.Combine(translationMatrix1, rotationMatrix1, scaleMatrix1);

	GLuint modelLoc1 = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model1));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);			// Draw Second Hex

	//		Create Camera One		//
	CCamera CamOne(program);
	mat4 view = CamOne.CameraView();

	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);

	glutSwapBuffers();
}

void CGameManager::Update()
{
	// Update information
	currentTime = glutGet(GLUT_ELAPSED_TIME);	// Get current time
	currentTime = currentTime * 0.001f;			// Converting to time seconds (From miliseconds)

	glutPostRedisplay();
}

GLint CGameManager::GenerateTextures()
{
	// Texture One
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image1 = SOIL_load_image("Resources/Textures/frogChair.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Texture Two
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image = SOIL_load_image("Resources/Textures/catz.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 1);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (0);
}

void CGameManager::ManagerMain()
{
	/// Register callbacks
	glutDisplayFunc(RenderRedirect);
	glutIdleFunc(UpdateRedirect);

	// Input glut callbacks
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MousePassiveMove);

	GenerateTextures();
	glutMainLoop();
}


void KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

void ProcessInput()
{
	if (KeyState['w'] == INPUT_DOWN)
	{
		objOne.y += 1.0f;
	}
	if (KeyState['s'] == INPUT_DOWN)
	{
		objOne.y -= 1.0f;
	}
	if (KeyState['d'] == INPUT_DOWN)
	{
		objOne.x += 1.0f;
	}
	if (KeyState['a'] == INPUT_DOWN)
	{
		objOne.x -= 1.0f;
	}
}

void MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
		return;

	MouseState[button] = (state == GLUT_DOWN) ? INPUT_DOWN : INPUT_UP;
}

void MousePassiveMove(int x, int y)
{
	cout << "Passive x: " << x << " | y: " << y << endl;
}

void MouseMove(int x, int y)
{
	cout << "Clicked x: " << x << " | y: " << y << endl;
}