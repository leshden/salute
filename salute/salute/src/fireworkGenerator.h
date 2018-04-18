#ifndef FIREWORK_GENERATOR_H
#define FIREWORK_GENERATOR_H
#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

class SceneObject;

// Represents a single particle and its state
struct ParticleFire {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	float Life;

	ParticleFire() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.
class FireworkGenerator
{
public:
	// Constructor
	FireworkGenerator(Shader shader, unsigned int amount, glm::vec2 position, float scale = 5.0f, float life = 1.0f, bool repeat = true);
	// Update all particles
	void Update(float dt, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	// Render all particles
	void Draw();
	bool isDeadGenerator();
private:
	// State
	bool _repeat;
	std::vector<ParticleFire> particles;
	unsigned int amount;
	glm::vec2 position;
	float scale;
	float life;
	// Render state
	Shader shader;
	unsigned int VAO;
	// Initializes buffer and vertex attributes
	void init();
};

#endif