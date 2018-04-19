#include "fireworkGenerator.h"
#include <glad/glad.h>
#include "constants.h"
#include <glm/gtc/matrix_transform.hpp>

FireworkGenerator::FireworkGenerator(Shader shader, unsigned int amount, glm::vec2 position, float scale, float life, bool repeat):
	shader(shader), amount(amount), position(position), scale(scale), life(life), _repeat(repeat)
{
	this->init();
}

void FireworkGenerator::Update(float dt)
{	
	for (unsigned int i = 0; i < this->amount; ++i)
	{
		ParticleFire &p = this->particles[i];
		p.Life -= dt; // reduce life
		p.Color.a -= dt * 0.5f;
		/*if (p.Life > 0.0f)
		{	
			p.Color.a -= dt * 2.5;
		}*/
	}
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
			//pointSize
			this->shader.SetFloat("pointSize", scale);
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_POINTS, 0, 1);
			glBindVertexArray(0);
		}
	}
}

bool FireworkGenerator::isDeadGenerator()
{
	for (ParticleFire particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			return false;
		}
	}

	return true;
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
		particle.Life = life;
		//respawnParticle(particle, glm::vec2(0), color);
		this->particles.push_back(particle);
	}
	
	float redColor = rand() % 2;
	float greenColor = rand() % 2;
	float blueColor = rand() % 2;
	if (!redColor && !greenColor && !blueColor) {
		redColor = 1.0f;
	}

	for (unsigned int i = 0; i < this->amount; i++) {
		particles[i].Position = position;
		do {

			float vx = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
			float vy = (rand() % 2 ? 1 : -1) * (rand() / (float)RAND_MAX * 5);
			glm::vec2 velocity = glm::vec2(vx, vy);
			particles[i].Velocity = velocity;
		} while (
			(particles[i].Velocity.x*particles[i].Velocity.x + particles[i].Velocity.y*particles[i].Velocity.y) > (rand() % 2 + 1));// 1

		particles[i].Color = glm::vec4(redColor, greenColor, blueColor ,1.0f);
	}
}
