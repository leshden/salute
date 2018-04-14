#ifndef SCENE_H
#define SCENE_H

#include<vector>

class SpriteRenderer;
class Background;
class SceneObject;
class ParticleGenerator;

class Scene
{
public:
	Scene(unsigned int width, unsigned int height);
	~Scene();

	void Init();

	void ProcessInput(float dt);
	void ProcessMouseButtonInput(double xpos, double ypos);
	void Update(float dt);
	void Render();
	void CheckOnDelete();
private :
	bool keys[1024];
	unsigned int  width;
	unsigned int height;
	SpriteRenderer* renderer;
	Background* background;
	SceneObject* object;
	ParticleGenerator* particles;
	std::vector<SceneObject*> _pVec;
	std::vector<ParticleGenerator*> _partVec;
};

#endif
