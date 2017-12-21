#include "Challenge_21.h"

Challenge_21::Challenge_21() {}
Challenge_21::~Challenge_21() {}

void Challenge_21::Run()
{
	P2();
}

void Challenge_21::P1()
{
	auto input = TxtFileGetLines("./Day_21/Input_21.txt");
	for (auto line : input)
	{
		line.erase(remove(line.begin(), line.end(), '/'), line.end());
		auto spacePos = line.find(' ');
		m_Rules.push_back(new Rule(line.substr(0, spacePos), line.substr(spacePos + 4)));
	}

	string image = ".#...####";
	for (int i = 0; i < 5; ++i)
	{
		UpdateImage(image);
	}

	int count = count_if(image.begin(), image.end(), [](char c) {return c == '#'; });
	cout << count << endl;
}

void Challenge_21::P2()
{
	auto input = TxtFileGetLines("./Day_21/Input_21.txt");
	for (auto line : input)
	{
		line.erase(remove(line.begin(), line.end(), '/'), line.end());
		auto spacePos = line.find(' ');
		m_Rules.push_back(new Rule(line.substr(0, spacePos), line.substr(spacePos + 4)));
	}

	string image = ".#...####";
	for (int i = 0; i < 18; ++i)
	{
		UpdateImage(image);
	}

	int count = count_if(image.begin(), image.end(), [](char c) {return c == '#'; });
	cout << count << endl;
}

string Challenge_21::GetSquare(const string& image, int topLeft)
{
	int size = 0;
	if (image.size() % 2 == 0)
		size = 2;
	else if (image.size() % 3 == 0)
		size = 3;
	else
		cout << "Wrong size in getsquare" << endl;

	int rowOffset = 0;
	string result;
	int imageSize = sqrt(image.size());

	int tlCol = topLeft % imageSize;
	int tlRow = topLeft / imageSize;
	for (int i = 0; i < size * size; ++i)
	{
		if (i % size == 0 && i != 0)
			++rowOffset;

		auto colOffset = i % size;
		auto col = tlCol + colOffset;
		auto row = tlRow + rowOffset;
		auto ind = col + row * imageSize;
		result += image[ind];
	}

	return result;
}

string Challenge_21::AssembleSquares(const vector<string>& sq)
{
	string result;
	int sqSize = sqrt(sq[0].size());
	int gridSize = sqrt(sq.size());

	for (int gr = 0; gr < gridSize; ++gr)
	{
		vector<string> useSquares;
		for (int sqr = 0; sqr < gridSize; ++sqr)
		{
			useSquares.push_back(sq[gr * gridSize + sqr]);
		}


		for (int sqRow = 0; sqRow < sqSize; ++sqRow)
		{
			for (auto s : useSquares)
			{
				result += GetRow(s, sqRow);
			}
		}

	}

	return result;
}

string Challenge_21::GetRow(const string& in, int row)
{
	int size = sqrt(in.size());
	return string(in.begin() + row * size, in.begin() + row * size + size);
}

vector<string> Challenge_21::FindSquares(const string& in)
{
	vector<string> squares;
	int col = 0;
	int row = 0;

	int size = 0;
	if (in.size() % 2 == 0)
		size = 2;
	else if (in.size() % 3 == 0)
		size = 3;

	int gridSize = sqrt(in.size());
	for (int i = 0; i < in.size(); i += size)
	{
		if (i % gridSize == 0 && i != 0)
		{
			i += (size-1) * gridSize;
		}

		if (i >= in.size())
			break;

		squares.push_back(GetSquare(in, i));
	}

	return squares;
}

void Challenge_21::TransformSquares(vector<string>& squares)
{
	for (auto& sq : squares)
	{
		for (auto r : m_Rules)
		{
			if (r->IsMatch(sq))
			{
				sq = r->output;
				break;
			}
		}
	}
}

void Challenge_21::PrintSquare(const string& in)
{
	int size = sqrt(in.size());
	for (int i = 0; i < in.size(); ++i)
	{
		if (i % size == 0 && i != 0)
			cout << endl;

		cout << in[i];
	}
	cout << endl;
}

void Challenge_21::UpdateImage(string& in)
{
	auto squares = FindSquares(in);
	TransformSquares(squares);
	in = AssembleSquares(squares);
}
