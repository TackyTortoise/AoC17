#pragma once
#include "../Challenge.h"

class Challenge_06 :
	public Challenge
{
public:
	Challenge_06();
	~Challenge_06();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

