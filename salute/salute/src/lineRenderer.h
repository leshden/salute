#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include <glm/glm.hpp>
#include "shader.h"

class LineRenderer
{
public:
	// Constructor (inits shaders/shapes)
	LineRenderer(Shader &shader);
	// Destructor
	~LineRenderer();
	// Renders a defined quad textured with given sprite
	void DrawLine(glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};
#endif