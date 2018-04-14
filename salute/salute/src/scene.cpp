#include "scene.h"
#include "resourceManager.h"
#include "spriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "background.h"
#include "sceneObject.h"
#include "particleGenerator.h"
#include <iostream>

Scene::Scene(unsigned int width, unsigned int height):
width(width), 
height(height),
renderer(nullptr),
background(nullptr),
object(nullptr),
particles(nullptr)
{
	
}

Scene::~Scene()
{
	delete renderer;
	delete background;
	delete object;
	delete particles;
}

void Scene::Init()
{
	// Load shaders
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\sprite.vs", "..\\salute\\src\\shaders\\sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\clouds.vs", "..\\salute\\src\\shaders\\clouds.fs", nullptr, "background");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\particle.vs", "..\\salute\\src\\shaders\\particle.fs", nullptr, "particle");
	// Load textures
	ResourceManager::LoadTexture("..\\salute\\res\\face.png", true, "face");
	ResourceManager::LoadTexture("..\\salute\\res\\particle.png", true, "particle");

	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);

	ResourceManager::GetShader("particle")->Use();
	ResourceManager::GetShader("particle")->SetMatrix4("projection", projection);
	
	// Set render-specific controls
	renderer = new SpriteRenderer(*ResourceManager::GetShader("sprite"));
	background = new Background();
	particles = new ParticleGenerator(*ResourceManager::GetShader("particle"), ResourceManager::GetTexture("face"), 100, glm::vec2(400, 300));
	object = new SceneObject(glm::vec2(400, 300), glm::vec2(100, 100), ResourceManager::GetTexture("face"));
}

void Scene::Update(float dt)
{
	particles->Update(dt, *object, 20, glm::vec2(10));
	for (ParticleGenerator* pg : _partVec) {
		pg->Update(dt, *object, 20, glm::vec2(10));
	}
}


void Scene::ProcessInput(float dt)
{

}

void Scene::ProcessMouseButtonInput(double xpos, double ypos)
{
	std::cout << "xpos: " << xpos << std::endl;
	std::cout << "ypos: " << ypos << std::endl; 
	_partVec.push_back(new ParticleGenerator(*ResourceManager::GetShader("particle"), ResourceManager::GetTexture("face"), 100, glm::vec2(xpos, ypos)));
	//_pVec.push_back(new SceneObject(glm::vec2(xpos, ypos), glm::vec2(100, 100), ResourceManager::GetTexture("face")));
	//new SceneObject(glm::vec2(xpos, ypos), glm::vec2(100, 100), ResourceManager::GetTexture("face"));
	//_partVec.push_back();
}

void Scene::Render()
{
	background->draw();
	renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(0, 0), glm::vec2(300, 400));
	for (SceneObject* so : _pVec) {
		so->Draw(*renderer);
	}
	for (ParticleGenerator* pg : _partVec) {
		pg->Draw();
	}
	//object->Draw(*renderer);
	particles->Draw();
}

void Scene::CheckOnDelete()
{
}
