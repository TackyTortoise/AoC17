#include "Challenge_03.h"

Challenge_03::Challenge_03(){}
Challenge_03::~Challenge_03(){}

void Challenge_03::Run()
{
	P2();
}

void Challenge_03::P1()
{
	int input = 347991;
	int square = sqrt(input);
	if (square % 2 == 0)
		--square;
	int botRight = pow(square, 2);
	int offset = square / 2;

	int base = botRight + 1;
	int o = input - base;
	int x = 0, y = 0;
	if (o <= (offset+1) * 4)
	{
		x = o - square;
		y = o - x;
		if (o < square)
		{
			++x;
			--y;
		}
	}
	else
	{
		botRight = pow(square + 2, 2);
		offset = (square + 2) / 2;
		base = botRight + 1;
		o = base - input;
		y = o - (square + 2);
		x = o - y;
		if (o < square + 2)
		{
			x = x - abs(y);
			y = 0;
		}
	}

	int curX = offset - (x - 1);
	int curY = offset - y;
	int manhatten = abs(curX) + abs(curY);
	cout << manhatten << endl;
}

void Challenge_03::P2()
{
	int input = 347991;

	vector<Cell> grid;
	grid.push_back(Cell(0, 0, 1));
	int currentSize = 1;
	int sign = 1;
	int cX = 0, cY = 0;

	int lastValue = 1;
	while (lastValue < input)
	{
		for (int x = 0; x < currentSize; ++x)
		{
			cX += sign * 1;
			int v = GetNeighboorSum(grid, cX, cY);
			grid.push_back(Cell(cX, cY, v));
			lastValue = v;
			if (lastValue > input)
				break;
		}
		if (lastValue > input)
			break;
		for (int y = 0; y < currentSize; ++y)
		{
			cY += -sign * 1;
			int v = GetNeighboorSum(grid, cX, cY);
			grid.push_back(Cell(cX, cY, v));
			lastValue = v;
			if (lastValue > input)
				break;
		}

		++currentSize;
		sign = -sign;
	}

	cout << lastValue << endl;
}

int Challenge_03::GetNeighboorSum(const vector<Cell>& grid, const int x, const int y) const
{
	int sum = 0;
	//right neighboor
	int nx = x + 1, ny = y;
	sum += GetCellValue(grid, nx, ny);

	//top right neighboor
	nx = x + 1, ny = y - 1;
	sum += GetCellValue(grid, nx, ny);

	//top neighboor
	nx = x, ny = y - 1;
	sum += GetCellValue(grid, nx, ny);

	//top left neighboor
	nx = x - 1, ny = y - 1;
	sum += GetCellValue(grid, nx, ny);

	//left neighboor
	nx = x - 1, ny = y;
	sum += GetCellValue(grid, nx, ny);

	//bottom left neighboor
	nx = x - 1, ny = y + 1;
	sum += GetCellValue(grid, nx, ny);

	//bottom neighboor
	nx = x, ny = y + 1;
	sum += GetCellValue(grid, nx, ny);

	//bottom right neighboor
	nx = x + 1, ny = y + 1;
	sum += GetCellValue(grid, nx, ny);

	int t = 0;
	return sum;
}

int Challenge_03::GetCellValue(const vector<Cell>& grid, const int x, const int y) const
{
	auto found = find(grid.begin(), grid.end(), Cell(x, y, 0));
	if (found != grid.end())
	{
		return found->value;
	}

	return 0;
}
