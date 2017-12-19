#pragma once
#include "../Challenge.h"

class Challenge_20 : public Challenge
{
public:
	Challenge_20();
	~Challenge_20();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

