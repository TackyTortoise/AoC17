#pragma once
#include "../Challenge.h"

class Challenge_23 : public Challenge
{
public:
	Challenge_23();
	~Challenge_23();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

