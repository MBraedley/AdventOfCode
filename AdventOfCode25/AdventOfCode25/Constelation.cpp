#include "pch.h"
#include "Constelation.h"


Constelation::Constelation() : m_range(3)
{
}


Constelation::~Constelation()
{
}

bool Constelation::AddToConstelation(Pos4D point)
{
	if (m_points.size() == 0)
	{
		m_points.push_back(point);
		return true;
	}

	if (WithinRange(point))
	{
		m_points.push_back(point);
		return true;
	}
	return false;
}

int Constelation::GetDistance(Pos4D a, Pos4D b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z) + abs(a.t - b.t);
}

bool Constelation::WithinRange(Pos4D point)
{
	for (auto p : m_points)
	{
		if (GetDistance(p, point) <= m_range)
			return true;
	}
	return false;
}

Constelation operator+(Constelation & lhop, Constelation & rhop)
{
	Constelation sum;
	sum.m_range = lhop.m_range;
	sum.m_points.assign(lhop.m_points.begin(), lhop.m_points.end());
	sum.m_points.splice(sum.m_points.end(), rhop.m_points);

	return sum;
}

void operator+=(Constelation & lhs, Constelation & rhs)
{
	lhs = lhs + rhs;
}
