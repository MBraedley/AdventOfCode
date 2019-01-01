#pragma once
#include <list>

struct Pos4D
{
	int x;
	int y;
	int z;
	int t;
};

class Constelation
{
public:
	Constelation();
	~Constelation();

	bool AddToConstelation(Pos4D point);

	size_t Size() { return m_points.size(); }

	static int GetDistance(Pos4D a, Pos4D b);
	bool WithinRange(Pos4D point);

	friend Constelation operator+(Constelation& lhop, Constelation& rhop);
	friend void operator+=(Constelation& lhs, Constelation& rhs);

private:


	std::list<Pos4D> m_points;

	int m_range;
};

