#pragma once
#include "../Challenge.h"

class Challenge_04 :
	public Challenge
{
public:
	Challenge_04();
	~Challenge_04();

	void Run() override;

private:
	void P1() override;
	void P2() override;
};

