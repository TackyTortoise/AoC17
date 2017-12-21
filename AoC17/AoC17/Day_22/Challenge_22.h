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
};

