#include "fireworkGenerator.h"
#include <glad/glad.h>
#include "constants.h"
#include <glm/gtc/matrix_transform.hpp>

FireworkGenerator::FireworkGenerator(Shader shader, unsigned int amount, glm::vec2 position, float scale, float life, bool repeat):
	shader(shader), amount(amount), position(position), scale(scale), life(life), _repeat(repeat)
{
	this->init();
}

void FireworkGenerator::Update(float dt, unsigned int newParticles, glm::vec2 offset)
{
}

void FireworkGenerator::Draw()
{
	this->shader.Use();
	for (unsigned int i = 0; i < this->amount; i++) {
		//particles[i].Position.x += particles[i].Velocity.x;
		//particles[i].Position.y += particles[i].Velocity.y;
		if (particles[i].Position.x < SCR_WIDTH && particles[i].Position.x > 0
			&& particles[i].Position.y > 0 && particles[i].Position.y < SCR_HEIGHT) {
			
			particles[i].Position -= particles[i].Velocity *4.0f;
			particles[i].Velocity = glm::vec2(particles[i].Velocity.x, particles[i].Velocity.y+0.02f);
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(particles[i].Position, 0.0f));  // First translate
			this->shader.SetMatrix4("model", model);
			this->shader.SetVector4f("color", particles[i].Color);
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_POINTS, 0, 1);
			glBindVertexArray(0);
			
		/*	glBegin(GL_LINE_STRIP);
			glColor3ub(0, 0, 0);
			glVertex2i(stars[i].x - stars[i].vx * 4, stars[i].y - stars[i].vy * 4);
			glColor3ub(stars[i].r, stars[i].g, stars[i].b);
			glVertex2i(stars[i].x, stars[i].y);
			glEnd();*/
		}
		/*else {
			particles[i].Position = position;
			do {

				float vx = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
				float vy = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
				glm::vec2 velocity = glm::vec2(vx, vy);
				particles[i].Velocity = velocity;
			} while (
				(particles[i].Velocity.x*particles[i].Velocity.x + particles[i].Velocity.y*particles[i].Velocity.y) > 25);
		}*/
	}


	//// Use additive blending to give it a 'glow' effect
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//this->shader.Use();
	//for (ParticleFire particle : this->particles)
	//{
	//	if (particle.Life > 0.0f)
	//	{
	//		/*this->shader.SetFloat("scale", scale);
	//		this->shader.SetVector2f("offset", particle.Position);
	//		this->shader.SetVector4f("color", particle.Color);*/
	//		glBindVertexArray(this->VAO);
	//		glDrawArrays(GL_TRIANGLES, 0, 2);
	//		glBindVertexArray(0);
	//	}
	//}
	//// Don't forget to reset to default blending mode
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool FireworkGenerator::isDeadGenerator()
{
	return false;
}

void FireworkGenerator::init()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      
		0.0f,  0.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Create this->amount default particle instances
	//glm::vec3 color = generateColor();
	for (unsigned int i = 0; i < this->amount; ++i) {
		ParticleFire particle;
		//respawnParticle(particle, glm::vec2(0), color);
		this->particles.push_back(particle);
	}


	for (unsigned int i = 0; i < this->amount; i++) {
		particles[i].Position = position;
		do {

			float vx = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
			float vy = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
			glm::vec2 velocity = glm::vec2(vx, vy);
			particles[i].Velocity = velocity;
		} while (
			(particles[i].Velocity.x*particles[i].Velocity.x + particles[i].Velocity.y*particles[i].Velocity.y) > 1);

		particles[i].Color = glm::vec4((rand() % 101)/100, (rand() % 101) / 100, (rand() % 101) / 100,1.0f);
	}
}
