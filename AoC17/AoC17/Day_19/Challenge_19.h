#pragma once
#include "../Challenge.h"

class Challenge_19 : public Challenge
{
public:
	Challenge_19();
	~Challenge_19();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	string m_Buffer;

	enum Direction
	{
		Right,
		Down,
		Left,
		Up,
	};

	Direction m_CurrentDirection = Down;
	int m_BufferWidth, m_BufferHeight;

	char GetNextTile(int& index);
	Direction GetNewDirection(int index);
};

