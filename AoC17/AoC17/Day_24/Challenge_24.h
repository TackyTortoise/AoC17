#pragma once
#include "../Challenge.h"

class Challenge_24 : public Challenge
{
public:
	Challenge_24();
	~Challenge_24();
	void Run() override;
protected:
	void P1() override;
	void P2() override;
};

