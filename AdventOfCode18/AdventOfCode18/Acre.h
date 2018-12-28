#pragma once

class Acre
{
public:
	enum Type
	{
		Trees,
		Lumberyard,
		Open,
		LAST
	};

	Acre();
	~Acre();

	Type GetType() { return m_type; }
	void SetNextType(Type nextType) { m_nextType = nextType; }

	void Step() { m_type = m_nextType; }

private:
	Type m_type;
	Type m_nextType;
};

