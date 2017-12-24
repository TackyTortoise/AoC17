#pragma once
#include "../Challenge.h"

class Challenge_25 : public Challenge
{
public:
	Challenge_25();
	~Challenge_25();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

