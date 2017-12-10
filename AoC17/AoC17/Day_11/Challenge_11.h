#pragma once
#include "../Challenge.h"

class Challenge_11 : public Challenge
{
public:
	Challenge_11();
	~Challenge_11();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

