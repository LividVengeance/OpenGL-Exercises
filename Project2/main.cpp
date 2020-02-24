#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "ShaderLoader.h"


GLfloat currentTime;
GLuint texture;
GLint program;
GLfloat vertices[]{
	// Position				// Color			// Texture Coords
	-0.5f, -0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Top - Left
	 0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// Bot - Left
	 0.0f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Bot - Right
	 0.5f,  0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,	// Top - Right
};
GLuint indices[] = {
	0, 1, 2,	// First Triangle
	0, 2, 3,	// Second Triangle
};
GLuint VBO;
GLuint EBO;
GLuint VAO;


GLint GenerateTextures()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image = SOIL_load_image("Resources/Textures/catz.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
}

void Update()
{
	// Update information

	currentTime = glutGet(GLUT_ELAPSED_TIME);	// Get current time
	currentTime = currentTime * 0.001f;			// Converting to time seconds (From miliseconds)

	glutPostRedisplay();
}


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAO);		// Bind VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
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

	program = ShaderLoader::CreateProgram(	"Resources/Shaders/Basic.vs",
											"Resources/Shaders/Basic.fs");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	

	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	GenerateTextures();
	glutMainLoop();
	return(0);
}



