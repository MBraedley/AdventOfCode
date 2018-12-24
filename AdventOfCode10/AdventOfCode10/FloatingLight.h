#pragma once
class FloatingLight
{
public:
	FloatingLight(int x, int y, int velX, int velY);
	~FloatingLight();

	void step(int iterations = 1);

	int m_x;
	int m_y;
private:
	int m_velX;
	int m_velY;
};

