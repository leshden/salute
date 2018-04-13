#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 surface4Position;

//uniform mat4 model;
//uniform mat4 projection;

void main()
{
	gl_Position =  /*projection * model *  */vec4(aPos, 1.0);
	surface4Position = gl_Position;
}