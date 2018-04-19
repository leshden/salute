#include "scene.h"
#include "resourceManager.h"
#include "spriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"
#include "background.h"
#include "sceneObject.h"
#include "particleGenerator.h"
#include <iostream>
#include "lineRenderer.h"
#include "fireworkGenerator.h"

Scene::Scene(unsigned int width, unsigned int height):
width(width), 
height(height),
line(nullptr),
renderer(nullptr),
renderer3d(nullptr),
background(nullptr),
object(nullptr),
particles(nullptr)
{
	
}

Scene::~Scene()
{
	delete line;
	delete renderer3d;
	delete renderer;
	delete background;
	delete object;
	delete particles;
}

void Scene::Init()
{
	// Load shaders
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\sprite.vs", "..\\salute\\src\\shaders\\sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\sprite3d.vs", "..\\salute\\src\\shaders\\sprite3d.fs", nullptr, "sprite3d");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\clouds.vs", "..\\salute\\src\\shaders\\clouds.fs", nullptr, "background");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\particle.vs", "..\\salute\\src\\shaders\\particle.fs", nullptr, "particle");
	ResourceManager::LoadShader("..\\salute\\src\\shaders\\line.vs", "..\\salute\\src\\shaders\\line.fs", nullptr, "line");
	// Load textures
	ResourceManager::LoadTexture("..\\salute\\res\\face.png", true, "face");
	ResourceManager::LoadTexture("..\\salute\\res\\particle.png", true, "particle");
	ResourceManager::LoadTexture("..\\salute\\res\\sparkle.png", true, "sparkle");
	ResourceManager::LoadTexture("..\\salute\\res\\circle.png", true, "circle");
	// must be degree 2 ... 512, 1024...
	ResourceManager::LoadTexture("..\\salute\\res\\floor.png", false, "floor");
	ResourceManager::LoadTexture("..\\salute\\res\\wall.png", false, "wall");

	// Configure shaders
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
	/*glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
	ResourceManager::GetShader("sprite3d")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite3d")->SetMatrix4("projection", projection);*/

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
	ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle")->Use();
	ResourceManager::GetShader("particle")->SetMatrix4("projection", projection);
	ResourceManager::GetShader("line")->Use();
	ResourceManager::GetShader("line")->SetMatrix4("projection", projection);
	
	// Set render-specific controls
	renderer = new SpriteRenderer(*ResourceManager::GetShader("sprite"));
	//renderer3d = new SpriteRenderer(*ResourceManager::GetShader("sprite3d"));
	background = new Background();

	line = new LineRenderer(*ResourceManager::GetShader("line"));
	//particles = new ParticleGenerator(*ResourceManager::GetShader("particle"), ResourceManager::GetTexture("sparkle"), 100, glm::vec2(400, 300));
	//object = new SceneObject(glm::vec2(400, 300), glm::vec2(100, 100), ResourceManager::GetTexture("face"));
}

void Scene::Update(float dt)
{
	//particles->Update(dt, *object, 20, glm::vec2(10));
	for (ParticleGenerator* pg : _partVec) {
		pg->Update(dt, 20, glm::vec2(10));
	}

	for (FireworkGenerator* fg : _fireVec) {
		fg->Update(dt);
	}
}


void Scene::ProcessInput(float dt)
{

}

void Scene::ProcessMouseButtonInput(double xpos, double ypos)
{
	std::cout << "xpos: " << xpos << std::endl;
	std::cout << "ypos: " << ypos << std::endl; 
	float scale = 2.0f + (float)(rand() % 6) / 10;// 2 - 2.5;
	float life = 2.0f;//rand() % 2 + 0.5f;
	//_partVec.push_back(new ParticleGenerator(*ResourceManager::GetShader("particle"), ResourceManager::GetTexture("circle"), 100, glm::vec2(xpos, ypos), scale, life, false));
	
	_fireVec.push_back(new FireworkGenerator(*ResourceManager::GetShader("line"), 400, glm::vec2(xpos, ypos), scale, life, false));
	//_pVec.push_back(new SceneObject(glm::vec2(xpos, ypos), glm::vec2(100, 100), ResourceManager::GetTexture("face")));
	//new SceneObject(glm::vec2(xpos, ypos), glm::vec2(100, 100), ResourceManager::GetTexture("face"));
	//_partVec.push_back();
}

void Scene::Render()
{
	background->draw();
	//renderer->DrawSprite(ResourceManager::GetTexture("wall"), glm::vec2(200, 200), glm::vec2(300, 300));
	//line->DrawLine(glm::vec2(200, 200), glm::vec2(50, 50));
	//renderer3d->DrawSprite3D(ResourceManager::GetTexture("wall"), glm::vec2(200, 200), glm::vec2(300, 300));
	for (SceneObject* so : _pVec) {
		so->Draw(*renderer);
	}
	/*for (ParticleGenerator* pg : _partVec) {
		pg->Draw();
	}*/

	for (FireworkGenerator* fg : _fireVec) {
		fg->Draw();
	}


	//object->Draw(*renderer);
	//particles->Draw();
}

void Scene::CheckOnDelete()
{
	std::vector<ParticleGenerator*> timeVecActive;
	std::vector<ParticleGenerator*> timeVecDisactive;
	for (ParticleGenerator* pg : _partVec) {
		if (!pg->isDeadGenerator()) {
			timeVecActive.push_back(pg);
		}
		else {
			timeVecDisactive.push_back(pg);
		}
	}
	if (!timeVecDisactive.empty()) {
		for (ParticleGenerator* pg : timeVecDisactive) {
			delete pg;
		}

		_partVec.clear();

		for (ParticleGenerator* pg : timeVecActive) {
			_partVec.push_back(pg);
		}
	}
}

void Scene::CheckOnDeleteFirework() {
	std::vector<FireworkGenerator*> timeVecActive;
	std::vector<FireworkGenerator*> timeVecDisactive;
	for (FireworkGenerator* fg : _fireVec) {
		if (!fg->isDeadGenerator()) {
			timeVecActive.push_back(fg);
		}
		else {
			timeVecDisactive.push_back(fg);
		}
	}
	if (!timeVecDisactive.empty()) {
		for (FireworkGenerator* fg : timeVecDisactive) {
			delete fg;
		}

		_fireVec.clear();

		for (FireworkGenerator* fg : timeVecActive) {
			_fireVec.push_back(fg);
		}
	}
}
