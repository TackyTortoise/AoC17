#pragma once
#include "../Challenge.h"

class Challenge_03 :public Challenge
{
public:
	Challenge_03();
	~Challenge_03();

	void Run() override;

private:
	void P1() override;
	void P2() override;

	struct Cell
	{
		Cell(int myX, int myY, int myValue)
		{
			x = myX;
			y = myY;
			value = myValue;
		}
		int x;
		int y;
		int value;

		friend bool operator==(const Cell& t, const Cell& o)
		{
			return t.x == o.x && t.y == o.y;
		}
	};

	int GetNeighboorSum(const vector<Cell>& grid, const int x, const int y) const;
	int GetCellValue(const vector<Cell>& grid, const int x, const int y) const;
};

