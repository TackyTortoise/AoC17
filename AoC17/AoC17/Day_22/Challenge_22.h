#pragma once
#include "../Challenge.h"

class Challenge_22 :	public Challenge
{
public:
	Challenge_22();
	~Challenge_22();
	void Run() override;
protected:
	void P1() override;
	void P2() override;

private:
	struct Node
	{
		Node(int vX, int vY, char vState = 'I'):x(vX), y(vY), state(vState){}
		int x = 0;
		int y = 0;
		char state; // I = infected, F = flagged, W = Weakened, C = Clean

		bool operator==(const Node& o) const
		{
			return x == o.x && y == o.y;
		}
	};	

	void MoveVirusForward(Node& n, int direction);
};