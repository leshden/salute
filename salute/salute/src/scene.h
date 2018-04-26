#ifndef SCENE_H
#define SCENE_H

#include<vector>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer;
class Background;
class SceneObject;
class ParticleGenerator;
class LineRenderer;
class FireworkGenerator;

class vec3;
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
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
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
