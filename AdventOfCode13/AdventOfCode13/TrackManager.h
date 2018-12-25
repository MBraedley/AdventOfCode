#pragma once
#include <string>
#include <vector>
#include <set>
#include <memory>

#include "Minecart.h"

class TrackManager
{
public:
	TrackManager(std::string trackFile);
	~TrackManager();

	bool MoveCarts();
	Location GetCrash() { return m_crashSpot; }
	Location GetLast();

private:
	void LoadTrack(std::string trackFile);
	void FindCarts();

	bool MoveCart(Minecart& cart);

	std::set<Minecart> m_unmovedMinecarts;
	std::vector<Minecart> m_minecarts;
	std::set<Minecart> m_movedMinecarts;

	std::vector<std::string> m_track;

	Location m_crashSpot;
};

