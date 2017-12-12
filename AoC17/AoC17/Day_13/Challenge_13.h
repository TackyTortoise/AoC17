#pragma once
#include "../Challenge.h"

class Challenge_13 : public Challenge
{
public:
	Challenge_13();
	~Challenge_13();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

