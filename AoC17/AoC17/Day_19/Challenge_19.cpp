#include "Challenge_19.h"

Challenge_19::Challenge_19() {}
Challenge_19::~Challenge_19() {}

void Challenge_19::Run()
{
	P2();
}

void Challenge_19::P1()
{
	auto lines = TxtFileGetLines("./Day_19/Input_19.txt");
	m_BufferWidth = lines[0].size();
	m_BufferHeight = lines.size();
	m_Buffer = TxtFileToString("./Day_19/Input_19.txt");
	m_Buffer.erase(std::remove(m_Buffer.begin(), m_Buffer.end(), '\n'), m_Buffer.end());
	int index = m_Buffer.find('|');
	char curTile = '|';
	string result = "";
	while (curTile != ' ')
	{
		curTile = GetNextTile(index);
		if (curTile == '+')
			m_CurrentDirection = GetNewDirection(index);
		if (isalpha(curTile))
			result += curTile;
	}
	cout << result;
}

void Challenge_19::P2()
{
	auto lines = TxtFileGetLines("./Day_19/Input_19.txt");
	m_BufferWidth = lines[0].size();
	m_BufferHeight = lines.size();
	m_Buffer = TxtFileToString("./Day_19/Input_19.txt");
	m_Buffer.erase(std::remove(m_Buffer.begin(), m_Buffer.end(), '\n'), m_Buffer.end());
	int index = m_Buffer.find('|');
	char curTile = '|';
	int steps = 0;
	while (curTile != ' ')
	{
		curTile = GetNextTile(index);
		++steps;
		if (curTile == '+')
			m_CurrentDirection = GetNewDirection(index);
	}

	cout << steps << endl;
}

char Challenge_19::GetNextTile(int& index)
{
	int c = index % m_BufferWidth;
	int r = index / m_BufferWidth;
	switch (m_CurrentDirection)
	{
	case Right: 
		if (c < m_BufferWidth - 1)
		{
			++index;
			return m_Buffer[index];
		}
		break;
	case Down: 
		if (r < m_BufferHeight - 1)
		{
			index += m_BufferWidth;
			return m_Buffer[index];
		}
		break;
	case Left: 
		if (c > 0)
		{
			--index;
			return m_Buffer[index];
		}
		break;
	case Up: 
		if (r > 0)
		{
			index -= m_BufferWidth;
			return m_Buffer[index];
		}
		break;
	}

	return ' ';
}

Challenge_19::Direction Challenge_19::GetNewDirection(int index)
{
	int c = index % m_BufferWidth;
	int r = index / m_BufferWidth;

	if (c < m_BufferWidth - 1 && m_Buffer[index + 1] != ' ' && m_CurrentDirection != Right && m_CurrentDirection != Left)
		return Right;

	if (r < m_BufferHeight - 1 && m_Buffer[index + m_BufferWidth] != ' ' && m_CurrentDirection != Down && m_CurrentDirection != Up)
		return Down;

	if (c > 0 && m_Buffer[index - 1] != ' ' && m_CurrentDirection != Left && m_CurrentDirection != Right)
		return Left;

	if (r > 0 && m_Buffer[index - m_BufferWidth] != ' ' && m_CurrentDirection != Up && m_CurrentDirection != Down)
		return Up;
}
