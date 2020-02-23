#include <glew.h>
#include <freeglut.h>
#include <iostream>

#include "ShaderLoader.h"


GLfloat currentTime;

GLint program;
GLfloat vertices[]{
	// Position				// Color
	-0.5f, -0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	// Left
	 0.5f, -0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	// Right
	 0.0f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	// Top
};
GLuint VBO;
GLuint VAO;



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

	program = ShaderLoader::CreateProgram(	"Resources/Shaders/Basic.vs",
											"Resources/Shaders/Basic.fs");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),	// Stride of the single vertex (pos + color)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutMainLoop();
	return(0);
}



