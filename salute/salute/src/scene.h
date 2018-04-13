#ifndef SCENE_H
#define SCENE_H

class SpriteRenderer;
class Background;
class SceneObject;

class Scene
{
public:
	Scene(unsigned int width, unsigned int height);
	~Scene();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
private :
	bool keys[1024];
	unsigned int  width;
	unsigned int height;
	SpriteRenderer* renderer;
	Background* background;
	SceneObject* object;
};

#endif
