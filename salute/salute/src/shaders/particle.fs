#version 330 core
in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 color;

uniform sampler2D sprite;

void main()
{
	vec4 texColor = texture(sprite, TexCoords);
	if(texColor.a < 0.1)
		discard;
	color = texColor * ParticleColor;
	
	//vec4 texColor = (texture(sprite, TexCoords) * ParticleColor);
   // if(texColor.x == 1.0 && texColor.y == 1.0 && texColor.z == 1.0)
     //  discard;
   // color = texColor;//(texture(sprite, TexCoords) * ParticleColor);
} 