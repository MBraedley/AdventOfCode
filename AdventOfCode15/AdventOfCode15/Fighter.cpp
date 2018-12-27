#include "pch.h"
#include "Fighter.h"


Fighter::Fighter(Location loc, int ap /*= 3*/) : m_attack(ap), m_hp(200), m_location(loc)
{
}


Fighter::~Fighter()
{
}
