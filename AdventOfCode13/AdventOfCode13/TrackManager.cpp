#include "pch.h"
#include "TrackManager.h"
#include <fstream>
#include <iostream>

TrackManager::TrackManager(std::string trackFile)
{
	LoadTrack(trackFile);
	FindCarts();
}


TrackManager::~TrackManager()
{
}

bool TrackManager::MoveCarts()
{
	for (auto& it : m_minecarts)
	{
		size_t numErased = m_unmovedMinecarts.erase(it);
		if (numErased == 1)
		{
			if (!MoveCart(it))
			{
				m_unmovedMinecarts.erase(it);
				m_movedMinecarts.erase(it);
				m_crashSpot = it.m_location;
			}
			else
				m_movedMinecarts.insert(it);
		}
		else if (numErased > 1)
		{
			std::cout << "Something went wrong";
			return false;
		}
	}
	m_minecarts.clear();
	m_minecarts.assign(m_movedMinecarts.begin(), m_movedMinecarts.end());
	m_unmovedMinecarts = m_movedMinecarts;
	m_movedMinecarts.clear();
	return m_minecarts.size() > 1;
}

Location TrackManager::GetLast()
{
	if (m_minecarts.size() == 1)
		return m_minecarts[0].m_location;
	
	Location loc;
	loc.x = -1;
	loc.y = -1;
	return loc;
}

void TrackManager::LoadTrack(std::string trackFile)
{
	std::ifstream fin(trackFile);

	std::string line;
	while (getline(fin, line))
	{
		m_track.push_back(line);
	}
}

void TrackManager::FindCarts()
{
	for (int row = 0; row < m_track.size(); row++)
	{
		int col;
		while ((col = m_track[row].find_first_of('>')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			Minecart cart(loc, RIGHT);
			m_unmovedMinecarts.insert(cart);
			m_track[row][col] = '-';
		}
		while ((col = m_track[row].find_first_of('<')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			Minecart cart(loc, LEFT);
			m_unmovedMinecarts.insert(cart);
			m_track[row][col] = '-';
		}
		while ((col = m_track[row].find_first_of('^')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			Minecart cart(loc, UP);
			m_unmovedMinecarts.insert(cart);
			m_track[row][col] = '|';
		}
		while ((col = m_track[row].find_first_of('v')) != std::string::npos)
		{
			Location loc;
			loc.x = col;
			loc.y = row;
			Minecart cart(loc, DOWN);
			m_unmovedMinecarts.insert(cart);
			m_track[row][col] = '|';
		}
	}
	m_minecarts.assign(m_unmovedMinecarts.begin(), m_unmovedMinecarts.end());
}

bool TrackManager::MoveCart(Minecart& cart)
{
	Location loc;
	switch (cart.m_facing)
	{
	case UP:
		cart.m_location.y--;
		loc = cart.m_location;
		if (m_track[loc.y][loc.x] == '+')
		{
			if (cart.m_nextTurn == STRAIGHT)
			{
				cart.m_nextTurn = TURN_RIGHT;
			}
			else if (cart.m_nextTurn == TURN_RIGHT)
			{
				cart.m_facing = RIGHT;
				cart.m_nextTurn = TURN_LEFT;
			}
			else if (cart.m_nextTurn == TURN_LEFT)
			{
				cart.m_facing = LEFT;
				cart.m_nextTurn = STRAIGHT;
			}
		}
		else if (m_track[loc.y][loc.x] == '\\')
		{
			cart.m_facing = LEFT;
		}
		else if (m_track[loc.y][loc.x] == '/')
		{
			cart.m_facing = RIGHT;
		}
		else if (m_track[loc.y][loc.x] == ' ')
		{
			std::cout << "Minecart off the tracks!" << std::endl;
			return false;
		}
		break;
	case DOWN:
		cart.m_location.y++;
		loc = cart.m_location;
		if (m_track[loc.y][loc.x] == '+')
		{
			if (cart.m_nextTurn == STRAIGHT)
			{
				cart.m_nextTurn = TURN_RIGHT;
			}
			else if (cart.m_nextTurn == TURN_RIGHT)
			{
				cart.m_facing = LEFT;
				cart.m_nextTurn = TURN_LEFT;
			}
			else if (cart.m_nextTurn == TURN_LEFT)
			{
				cart.m_facing = RIGHT;
				cart.m_nextTurn = STRAIGHT;
			}
		}
		else if (m_track[loc.y][loc.x] == '\\')
		{
			cart.m_facing = RIGHT;
		}
		else if (m_track[loc.y][loc.x] == '/')
		{
			cart.m_facing = LEFT;
		}
		else if (m_track[loc.y][loc.x] == ' ')
		{
			std::cout << "Minecart off the tracks!" << std::endl;
			return false;
		}
		break;
	case LEFT:
		cart.m_location.x--;
		loc = cart.m_location;
		if (m_track[loc.y][loc.x] == '+')
		{
			if (cart.m_nextTurn == STRAIGHT)
			{
				cart.m_nextTurn = TURN_RIGHT;
			}
			else if (cart.m_nextTurn == TURN_RIGHT)
			{
				cart.m_facing = UP;
				cart.m_nextTurn = TURN_LEFT;
			}
			else if (cart.m_nextTurn == TURN_LEFT)
			{
				cart.m_facing = DOWN;
				cart.m_nextTurn = STRAIGHT;
			}
		}
		else if (m_track[loc.y][loc.x] == '\\')
		{
			cart.m_facing = UP;
		}
		else if (m_track[loc.y][loc.x] == '/')
		{
			cart.m_facing = DOWN;
		}
		else if (m_track[loc.y][loc.x] == ' ')
		{
			std::cout << "Minecart off the tracks!" << std::endl;
			return false;
		}
		break;
	case RIGHT:
		cart.m_location.x++;
		loc = cart.m_location;
		if (m_track[loc.y][loc.x] == '+')
		{
			if (cart.m_nextTurn == STRAIGHT)
			{
				cart.m_nextTurn = TURN_RIGHT;
			}
			else if (cart.m_nextTurn == TURN_RIGHT)
			{
				cart.m_facing = DOWN;
				cart.m_nextTurn = TURN_LEFT;
			}
			else if (cart.m_nextTurn == TURN_LEFT)
			{
				cart.m_facing = UP;
				cart.m_nextTurn = STRAIGHT;
			}
		}
		else if (m_track[loc.y][loc.x] == '\\')
		{
			cart.m_facing = DOWN;
		}
		else if (m_track[loc.y][loc.x] == '/')
		{
			cart.m_facing = UP;
		}
		else if (m_track[loc.y][loc.x] == ' ')
		{
			std::cout << "Minecart off the tracks!" << std::endl;
			return false;
		}
		break;
	default:
		std::cout << "Minecart travelling in unknown direction!" << std::endl;
		break;
	}

	auto preIt = m_unmovedMinecarts.find(cart);
	auto postIt = m_movedMinecarts.find(cart);
	return (preIt == m_unmovedMinecarts.end() && postIt == m_movedMinecarts.end());
}
