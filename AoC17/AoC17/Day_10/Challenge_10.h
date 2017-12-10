#pragma once
#include "../Challenge.h"

class Challenge_10 : public Challenge
{
public:
	Challenge_10();
	~Challenge_10();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
	void ConvertASCIIToBytes(const string& input, vector<int>& output);
};

