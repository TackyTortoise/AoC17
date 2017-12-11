#include "Challenge_11.h"

Challenge_11::Challenge_11(){}
Challenge_11::~Challenge_11(){}

void Challenge_11::Run()
{
	P2();
}

void Challenge_11::P1()
{
	auto input = TxtFileToString("./Day_11/Input_11.txt");
	auto instructions = SplitString(input, ',');
	HexTile currentTile(0,0);
	for(string& instr : instructions)
	{
		if (instr == "n")
		{
			--currentTile.x;
			++currentTile.y;
		}
		else if (instr == "s")
		{
			++currentTile.x;
			--currentTile.y;
		}
		else if (instr == "ne")
		{
			++currentTile.y;
		}
		else if (instr == "nw")
		{
			--currentTile.x;
		}
		else if (instr == "se")
		{
			++currentTile.x;
		}
		else if (instr == "sw")
		{
			--currentTile.y;
		}
	}

	if (currentTile.x < 0 || currentTile.y < 0)
	{
		cout << max(abs(currentTile.x), abs(currentTile.y)) << endl;
	}
	else
		cout << currentTile.x + currentTile.y << endl;
}

void Challenge_11::P2()
{

	auto input = TxtFileToString("./Day_11/Input_11.txt");
	auto instructions = SplitString(input, ',');
	HexTile currentTile(0, 0);
	int highScore = numeric_limits<int>::min();
	for (string& instr : instructions)
	{
		if (instr == "n")
		{
			--currentTile.x;
			++currentTile.y;
		}
		else if (instr == "s")
		{
			++currentTile.x;
			--currentTile.y;
		}
		else if (instr == "ne")
		{
			++currentTile.y;
		}
		else if (instr == "nw")
		{
			--currentTile.x;
		}
		else if (instr == "se")
		{
			++currentTile.x;
		}
		else if (instr == "sw")
		{
			--currentTile.y;
		}
		int tileScore = 0;
		if (currentTile.x < 0 || currentTile.y < 0)
		{
			tileScore = max(abs(currentTile.x), abs(currentTile.y));
		}
		else
			tileScore = currentTile.x + currentTile.y;

		if (tileScore > highScore)
			highScore = tileScore;
	}

	cout << highScore << endl;
}
