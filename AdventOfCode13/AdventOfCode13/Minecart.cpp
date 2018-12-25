#include "pch.h"
#include "Minecart.h"


Minecart::Minecart(Location loc, Direction dir) : m_location(loc), m_facing(dir), m_nextTurn(TURN_LEFT)
{
}


Minecart::~Minecart()
{
}
