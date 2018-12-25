#pragma once

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

enum Turns
{
	TURN_LEFT = -1,
	STRAIGHT,
	TURN_RIGHT
};

struct Location
{
	int x;
	int y;
};

class Minecart
{
public:
	Minecart(Location loc, Direction dir);
	~Minecart();

	Location m_location;
	Direction m_facing;
	Turns m_nextTurn;

	friend bool operator< (const Minecart& lhs, const Minecart& rhs)
	{
		if (lhs.m_location.y != rhs.m_location.y)
			return lhs.m_location.y < rhs.m_location.y;
		return lhs.m_location.x < rhs.m_location.x;
	}
	friend bool operator> (const Minecart& lhs, const Minecart& rhs) { return rhs < lhs; }
	friend bool operator<=(const Minecart& lhs, const Minecart& rhs) { return !(lhs > rhs); }
	friend bool operator>=(const Minecart& lhs, const Minecart& rhs) { return !(lhs < rhs); }
	friend bool operator==(const Minecart& lhs, const Minecart& rhs) { return lhs.m_location.x == rhs.m_location.x && lhs.m_location.y == rhs.m_location.y; }
	friend bool operator!=(const Minecart& lhs, const Minecart& rhs) { return !(lhs == rhs); }
};

