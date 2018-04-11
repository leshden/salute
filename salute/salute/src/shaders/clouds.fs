#version 330 core

#define OCTAVES 6
uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;
in vec4 surface4Position;

float T = time*.1;
float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
	float fl = floor(p);
  float fc = fract(p);
	return mix(rand(fl), rand(fl + 1.0), fc);
}

float noise(vec2 n) {
	const vec2 d = vec2(0.0, 1.0);
  vec2 b = floor(n), f = smoothstep(vec2(0.0), vec2(1.0), fract(n));
	return mix(mix(rand(b), rand(b + d.yx), f.x), mix(rand(b + d.xy), rand(b + d.yy), f.x), f.y);
}


float fbm(vec2 pos)
{
	float accum = .0;
	float amp = 0.6;

	for(int i = 0; i < OCTAVES; i++)
	{
		vec2 c = vec2(1.);
		accum+= amp* noise(pos-0.9*c);
		pos *= 2.31;
		pos -= vec2(.6,0.2)*(T/amp);
		amp = amp*.5;
	}
	
	return accum;
}


float coverage = 0.45;//mouse.x;

vec2 surfacePosition = surface4Position.xy;
void main( void ) {	
	vec2 p = surfacePosition;
	p.x/=((.6+p.y)*1.);
	p.y = 1./(.6+p.y);
	
	float w = fbm(p*1.+T+.05);
	w=min(max(0.,w-coverage)*(1./coverage) ,1.);
	
	p = surfacePosition;
	p.x/=((.59+p.y)*1.);
	p.y = .9/(.59+p.y);
	
	
	float v = 1.*fbm(p*1.+T);
	
	v=max(0.,v-coverage*coverage);
	
	float sd = clamp(2.-length((surfacePosition+.5)-vec2(0.4, 0.4)),0.,2.);
	
	
	vec3 skycol = vec3(0.0);//mix(vec3( .1,0.4,.6),vec3( .2,0.1,.8),surfacePosition.y+.5);
	skycol+=vec3(1.,.9,0.5)*pow(sd,2.)*.2*coverage;
	
	vec3 col = min( (skycol+vec3(1.,.9,.4)*w*coverage),1.);
	
	col = mix(col,vec3(.3,.4,.5)*v*v*.1+coverage,v);
	
	
	gl_FragColor = vec4( col, 1. );

}