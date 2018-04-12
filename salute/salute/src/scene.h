#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>

class Scene
{
public:
	GLboolean              Keys[1024];
	GLuint                 Width, Height;

	Scene(GLuint width, GLuint height);
	~Scene();

	void Init();

	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

#endif
