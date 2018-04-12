#ifndef BACKGROUND_H
#define BACKGROUND_H
class Shader;

class Background {
public:
	Background();
	~Background();
	void draw();
private:
	void init();
private:
	unsigned int _VBO;
	unsigned int _VAO;
	double _timer;
	Shader *_shader;
};
#endif
