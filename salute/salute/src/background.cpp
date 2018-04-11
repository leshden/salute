#include "background.h"
#include "shader.h"
#include "constants.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const double DELTA = 0.02;

Background::Background():
_VBO(0),
_VAO(0),
_timer(0.0),
_shader(nullptr)
{
	init();
}

Background::~Background()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);

	delete _shader;
}

void Background::draw()
{

	// create transformations
	//glm::mat4 transform;
	//transform = glm::translate(transform, glm::vec3(0.5f, -1.0f, 0.0f));
	//transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//transform = glm::scale(transform, glm::vec3(1.5, 1.5, 1.5));
	_shader->use();
	
	//unsigned int transformLoc = glGetUniformLocation(_shader->ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	_shader->setFloat("time", (float)_timer);
	_shader->set2Float("resolution", 800, 600);
	_timer += DELTA;

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Background::init()
{
	_shader = new Shader("D:\\saluteproject\\salute\\salute\\src\\shaders\\clouds.vs", "D:\\saluteproject\\salute\\salute\\src\\shaders\\clouds.fs");

	float vertices[] = {
		// positions         
		-1.0f, -1.0f, 0.0f,   
		-1.0f, 1.0f, 0.0f, 
		1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
