#version 330 core

#define THICK 0.015

out vec4 FragColor;
uniform vec2 resolution;

float dl(vec2 p, vec2 a, vec2 b) {
	vec2 d = a - b;
	float k = dot(normalize(d), a - p);
	if (k < 0.0)
		return distance(p, a);
	if (k > length(d))
		return distance(p, b);
	return abs(dot(normalize(vec2(-d.y, d.x)), a - p));
}

float l(vec2 p, vec2 a, vec2 b, float r) {
	return 1.0 - smoothstep(r - THICK, r + THICK, dl(p, a, b));
}

float r(vec2 p, vec2 c, float o, float i, float t) {
	float d = distance(p, c);
	return smoothstep(i - t, i + t, d)
	     - smoothstep(o - t, o + t, d);
}
float r(vec2 p, vec2 c, float o, float i) {
	return r(p, c, o, i, THICK);
}

void main() {

	float a = resolution.x / resolution.y;
	vec2 p = vec2(a, 1.0) * gl_FragCoord.xy / resolution.xy;
	
	vec2 t = vec2(0.5*a, 0.92);
	vec2 bl = vec2(0.325*a, 0.275);
	vec2 br = vec2(0.675*a, 0.275);
	vec2 ml = vec2(0.4*a, 0.5);
	vec2 mr = vec2(0.6*a, 0.5);
	vec2 c = vec2(0.5*a, 0.5);
	
	float _l = l(p, bl, t, 0.05);
	float _l_ = l(p, ml, mr, 0.05);
	float l_ = l(p, br, t, 0.05);
	float o = r(p, c, 0.5, 0.4);
	
	float A = max(max(_l, _l_), max(l_, o));
	
	vec3 C = vec3(0.5426, 0.4574, 0.00);

	gl_FragColor = mix(vec4(A * C * 15.0, 1.0), vec4(C, 1.0), A);

}