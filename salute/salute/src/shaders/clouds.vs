#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 surface4Position;
uniform mat4 transform;

void main()
{
	gl_Position =  vec4(aPos, 1.0); // transform * vec4(aPos, 1.0);
	surface4Position = gl_Position;
}