#include "background.h"
#include "shader.h"
#include "constants.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "resourceManager.h"

const double DELTA = 0.02;
const std::string BACKGROUND_NAME = "background";

Background::Background():
_VBO(0),
_VAO(0),
_timer(0.0)
{
	init();
}

Background::~Background()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}

void Background::draw()
{

	// create transformations
	//glm::mat4 transform;
	//transform = glm::translate(transform, glm::vec3(0.5f, -1.0f, 0.0f));
	//transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//transform = glm::scale(transform, glm::vec3(1.5, 1.5, 1.5));
	//_shader->use();
	
	//unsigned int transformLoc = glGetUniformLocation(_shader->ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	
	Shader* shader = ResourceManager::GetShader(BACKGROUND_NAME);
	shader->Use();
	shader->SetFloat("time", (float)_timer);
	shader->SetVector2f("resolution", SCR_WIDTH, SCR_HEIGHT);
	_timer += DELTA;

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Background::init()
{
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\clouds.vs", "..\\salute\\src\\shaders\\clouds.fs", nullptr, BACKGROUND_NAME);

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
