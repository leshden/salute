#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
//uniform vec2 resolution;

void main()
{    
    //color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
	vec4 texColor = texture(image, TexCoords);
    if(texColor.a < 0.1)
        discard;

	vec4 colortest = vec4(1.0, 0.0,0.0,1.0);
	vec2 resolution = vec2(800, 600);

	vec2 center = vec2(400, 300);
	vec2 distance = center - (gl_FragCoord.xy / resolution);
	//vec2 mouse_distance = mouse - (gl_FragCoord.xy / resolution);
	
	//float red = 1.0 - length(distance);
	
	vec2 position = gl_FragCoord.xy / resolution.xy;

	//colortest.red = position.y;
	vec4 ff = vec4(0.0, position.y, 0.0 ,1.0);

	color = texture(image, TexCoords);// * ff;

	//float red = 1.0 - length(distance);
	//color = vec4(1.0, 0, 0, 1.0);

	//vec2 position = gl_FragCoord.xy / resolution.xy;
	//color.g = position.x;
} 