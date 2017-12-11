#pragma once
#include "../Challenge.h"

class Challenge_12 : public Challenge
{
public:
	Challenge_12();
	~Challenge_12();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

