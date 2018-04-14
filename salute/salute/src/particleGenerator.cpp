#include <glad/glad.h>
#include "particleGenerator.h"
#include "sceneObject.h"
#include "spriteRenderer.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount, glm::vec2 position, bool repeat)
	: shader(shader), texture(texture), amount(amount), position(position), _repeat(repeat)
{
	this->init();
}

void ParticleGenerator::Update(float dt, SceneObject &object, unsigned int newParticles, glm::vec2 offset)
{
	// Add new particles 
	if (_repeat) {
		glm::vec3 color = generateColor();
		for (unsigned int i = 0; i < newParticles; ++i)
		{
			int unusedParticle = this->firstUnusedParticle();
			this->respawnParticle(this->particles[unusedParticle], offset, color);
		}
	}
	// Update all particles
	for (unsigned int i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			p.Position -= p.Velocity * dt;
			p.Color.a -= dt * 2.5;
		}
	}
}

// Render all particles
void ParticleGenerator::Draw()
{
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.Use();
	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			this->shader.SetVector2f("offset", particle.Position);
			this->shader.SetVector4f("color", particle.Color);
			this->texture.Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
	// Set up mesh and attribute properties
	unsigned int VBO;
	float particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
	glBindVertexArray(0);

	// Create this->amount default particle instances
	glm::vec3 color = generateColor();
	for (unsigned int i = 0; i < this->amount; ++i) {
		Particle particle;
		respawnParticle(particle, glm::vec2(0), color);
		this->particles.push_back(particle);
	}
}

// Stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, glm::vec2 offset, glm::vec3 color)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	//float rColor = 0.5 + ((rand() % 100) / 100.0f);
	//float redColor = rand() % 2; 
	//float greenColor = rand() % 2;
	//float blueColor = rand() % 2;
	particle.Position = position;// +random + offset;
	particle.Color = glm::vec4(color.x, color.y, color.z, 1.0f);
	particle.Life = 1.0f;
	int velocityX = rand() % 200 - 100;
	int velocityY = rand() % 200 - 100;
	particle.Velocity = glm::vec2(-velocityX, -velocityY); //object.Velocity* 0.1f;
}

glm::vec3 ParticleGenerator::generateColor()
{
	float redColor = rand() % 2; 
	float greenColor = rand() % 2;
	float blueColor = rand() % 2;
	if (!redColor && !greenColor && !blueColor) {
		redColor = 1.0f;
	}
	return glm::vec3(redColor, greenColor, blueColor);
}
