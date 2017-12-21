#pragma once
#include "../Challenge.h"

class Challenge_21 : public Challenge
{
public:
	Challenge_21();
	~Challenge_21();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

