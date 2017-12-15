#pragma once
#include "../Challenge.h"

class Challenge_16 : public Challenge
{
public:
	Challenge_16();
	~Challenge_16();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

