#pragma once
#include "../Challenge.h"

class Challenge_14 : public Challenge
{
public:
	Challenge_14();
	~Challenge_14();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
	string HexStringToBinString(const string& hexStr);
	void ConvertASCIIToBytes(const string& input, vector<int>& output);
	string GetHash(const string& input);
	vector<int> GetActiveNeighbourIndices(const int ind, vector<char>& grid);
	void ClearNeighbours(const int ind, vector<char>& grid);
};

