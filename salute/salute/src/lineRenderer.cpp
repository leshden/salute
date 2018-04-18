#include "lineRenderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

LineRenderer::LineRenderer(Shader & shader)
{
	this->shader = shader;
	this->initRenderData();
}

LineRenderer::~LineRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void LineRenderer::DrawLine(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale
	this->shader.SetMatrix4("model", model);
	//glm::mat4 view;
	//// note that we're translating the scene in the reverse direction of where we want to move

	//view = glm::lookAt(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	////view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	//this->shader.SetMatrix4("view", view);

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_LINE_STRIP, 0, 2); // 2 indices for the 2 end points of 1 line

	glBindVertexArray(0);
}

void LineRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      
		0.0f,  0.0f, 0.0f,
		1.0f,  1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
