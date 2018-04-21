#ifndef SCENE_H
#define SCENE_H

#include<vector>

class SpriteRenderer;
class Background;
class SceneObject;
class ParticleGenerator;
class LineRenderer;
class FireworkGenerator;

class Scene
{
public:
	Scene(unsigned int width, unsigned int height);
	~Scene();

	void Init();

	void ProcessInput(float dt);
	void ProcessMouseButtonInput(double xpos, double ypos);
	void key_callback(int key, int action);
	void Update(float dt);
	void Render();
	void CheckOnDelete();
	void CheckOnDeleteFirework();
private :
	unsigned int  width;
	unsigned int height;
	LineRenderer* line;
	SpriteRenderer* renderer;
	SpriteRenderer* renderer3d;
	Background* background;
	SceneObject* object;
	ParticleGenerator* particles;
	std::vector<SceneObject*> _pVec;
	std::vector<ParticleGenerator*> _partVec;
	std::vector<FireworkGenerator*> _fireVec;
};

#endif
