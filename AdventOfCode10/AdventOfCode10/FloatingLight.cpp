#include "pch.h"
#include "FloatingLight.h"


FloatingLight::FloatingLight(int x, int y, int velX, int velY) : m_x(x), m_y(y), m_velX(velX), m_velY(velY)
{
}

FloatingLight::~FloatingLight()
{
}

void FloatingLight::step(int iterations)
{
	m_x += m_velX * iterations;
	m_y += m_velY * iterations;
}
